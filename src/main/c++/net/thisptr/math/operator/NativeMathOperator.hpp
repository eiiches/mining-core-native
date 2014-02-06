#ifndef _NATIVEMATHOPERATOR_HPP_
#define _NATIVEMATHOPERATOR_HPP_

typedef typename Eigen::Map<Eigen::VectorXd, Eigen::Aligned> DenseVector;
typedef typename Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>, Eigen::Aligned> DenseRowAligned;
typedef typename Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>, Eigen::Aligned> DenseColAligned;
typedef typename Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>, Eigen::Unaligned> DenseRowUnaligned;
typedef typename Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>, Eigen::Unaligned> DenseColUnaligned;

#define GetBufferPointer(env, buf, offset) \
	((double *) ((unsigned char *) (env)->GetDirectBufferAddress(buf) + (offset)))

struct JavaDenseMatrix {
	double *ptr;
	int rows;
	int columns;
	bool row_major;

	JavaDenseMatrix(double* ptr, int rows, int columns, bool row_major)
		: ptr(ptr), rows(rows), columns(columns), row_major(row_major) {}

	inline bool is_aligned() {
		return (((size_t) ptr) & 0xf) == 0;
	}
};

template <
	template <typename...> class Op,
	class Enable = void,
	typename... InputArgs
>
struct Apply;

template <
	template <typename...> class Op,
	typename InputArgsHead,
	typename... InputArgsRest
>
struct Apply<
	Op,
	typename std::enable_if<
		std::is_same<
			typename std::remove_reference<InputArgsHead>::type,
			JavaDenseMatrix
		>::value
	>::type,
	InputArgsHead,
	InputArgsRest...
>
{
	template <typename... CallArgs>
	static inline void apply(InputArgsHead&& jm, InputArgsRest&&... iargs, CallArgs&&... cargs) {
		if (jm.is_aligned()) {
			if (jm.row_major) {
				DenseRowAligned m(jm.ptr, jm.rows, jm.columns);
				Apply<Op, void, InputArgsRest...>::apply(std::forward<InputArgsRest>(iargs)..., std::forward<CallArgs>(cargs)..., m);
			} else {
				DenseColAligned m(jm.ptr, jm.rows, jm.columns);
				Apply<Op, void, InputArgsRest...>::apply(std::forward<InputArgsRest>(iargs)..., std::forward<CallArgs>(cargs)..., m);
			}
		} else {
			if (jm.row_major) {
				DenseRowUnaligned m(jm.ptr, jm.rows, jm.columns);
				Apply<Op, void, InputArgsRest...>::apply(std::forward<InputArgsRest>(iargs)..., std::forward<CallArgs>(cargs)..., m);
			} else {
				DenseColUnaligned m(jm.ptr, jm.rows, jm.columns);
				Apply<Op, void, InputArgsRest...>::apply(std::forward<InputArgsRest>(iargs)..., std::forward<CallArgs>(cargs)..., m);
			}
		}
	}
};

template <
	template <typename...> class Op,
	typename InputArgsHead,
	typename... InputArgsRest
>
struct Apply<
	Op,
	typename std::enable_if<
		!std::is_same<
			typename std::remove_reference<InputArgsHead>::type,
			JavaDenseMatrix
		>::value
	>::type,
	InputArgsHead,
	InputArgsRest...
>
{
	template <typename... CallArgs>
	static inline void apply(InputArgsHead&& ihead, InputArgsRest&&... iargs, CallArgs&&... cargs) {
		Apply<Op, void, InputArgsRest...>::apply(std::forward<InputArgsRest>(iargs)..., std::forward<CallArgs>(cargs)..., std::forward<InputArgsHead>(ihead));
	}
};

template <
	template <typename...> class Op
>
struct Apply<Op> {
	template <typename... CallArgs>
	static inline void apply(CallArgs&&... cargs) {
		Op<CallArgs...>()(std::forward<CallArgs>(cargs)...);
	}
};

template <
	template <typename...> class Op,
	typename... InputArgs
>
inline void apply(InputArgs&&... iargs) {
	Apply<Op, void, InputArgs...>::apply(std::forward<InputArgs>(iargs)...);
}

#endif /* _NATIVEMATHOPERATOR_HPP_ */
