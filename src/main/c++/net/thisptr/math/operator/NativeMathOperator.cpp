#include <Eigen/Core>
#include <jni.h>
#include <net_thisptr_math_operator_NativeMathOperator.h>

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
};

extern void *enabler;

template <template <typename...> class Op, typename... Args>
void call(Args&&... args) {
	Op<Args...>()(std::forward<Args>(args)...);
}

template <
	template <typename ...> class Op,
	typename A,
	typename B,
	typename C,
	typename... Rest,
	typename std::enable_if<!std::is_same<typename std::remove_reference<A>::type, JavaDenseMatrix>::value>::type *& = enabler,
	typename std::enable_if<!std::is_same<typename std::remove_reference<B>::type, JavaDenseMatrix>::value>::type *& = enabler,
	typename std::enable_if<!std::is_same<typename std::remove_reference<C>::type, JavaDenseMatrix>::value>::type *& = enabler
>
void call(A&& a, B&& b, C&& c, JavaDenseMatrix& d, Rest&&... rest) {
	if (d.row_major) {
		DenseRowUnaligned _d(d.ptr, d.rows, d.columns);
		call<Op>(a, b, c, _d, std::forward<Rest>(rest)...);
	} else {
		DenseColUnaligned _d(d.ptr, d.rows, d.columns);
		call<Op>(a, b, c, _d, std::forward<Rest>(rest)...);
	}
}


template <
	template <typename ...> class Op,
	typename A,
	typename B,
	typename... Rest,
	typename std::enable_if<!std::is_same<typename std::remove_reference<A>::type, JavaDenseMatrix>::value>::type *& = enabler,
	typename std::enable_if<!std::is_same<typename std::remove_reference<B>::type, JavaDenseMatrix>::value>::type *& = enabler
>
void call(A&& a, B&& b, JavaDenseMatrix& c, Rest&&... rest) {
	if (c.row_major) {
		DenseRowUnaligned _c(c.ptr, c.rows, c.columns);
		call<Op>(a, b, _c, std::forward<Rest>(rest)...);
	} else {
		DenseColUnaligned _c(c.ptr, c.rows, c.columns);
		call<Op>(a, b, _c, std::forward<Rest>(rest)...);
	}
}

template <
	template <typename ...> class Op,
	typename A,
	typename... Rest,
	typename std::enable_if<!std::is_same<typename std::remove_reference<A>::type, JavaDenseMatrix>::value>::type *& = enabler
>
void call(A&& a, JavaDenseMatrix& b, Rest&&... rest) {
	if (b.row_major) {
		DenseRowUnaligned _b(b.ptr, b.rows, b.columns);
		call<Op>(a, _b, std::forward<Rest>(rest)...);
	} else {
		DenseColUnaligned _b(b.ptr, b.rows, b.columns);
		call<Op>(a, _b, std::forward<Rest>(rest)...);
	}
}

template <
	template <typename ...> class Op,
	typename... Rest
>
void call(JavaDenseMatrix& a, Rest&&... rest) {
	if (a.row_major) {
		DenseRowUnaligned _a(a.ptr, a.rows, a.columns);
		call<Op>(_a, std::forward<Rest>(rest)...);
	} else {
		DenseColUnaligned _a(a.ptr, a.rows, a.columns);
		call<Op>(_a, std::forward<Rest>(rest)...);
	}
}

template <typename R, typename X, typename Y, typename S>
struct AssignMultiplyMatrixMatrixScaler {
	void operator()(R& r, X& x, Y& y, double s) {
		r.noalias() = x * y * s;
	}
};

template <typename R, typename X, typename Y>
struct AssignMultiplyMatrixMatrix {
	void operator()(R& r, X& x, Y& y) {
		r.noalias() = x * y;
	}
};

template <typename R, typename X, typename Y, typename S>
struct AddMultiplyMatrixMatrixScaler {
	void operator()(R& r, X& x, Y& y, double s) {
		r.noalias() += x * y * s;
	}
};

template <typename R, typename X, typename S>
struct AddMultiplyMatrixScaler {
	void operator()(R& r, X& x, double s) {
		r.noalias() += x * s;
	}
};

template <typename M>
struct AssignZeroMatrix {
	void operator()(M& m) {
		m.setZero();
	}
};

template <typename R, typename X, typename S>
struct AssignMultiplyMatrixScaler {
	void operator()(R& r, X& x, double s) {
		r.noalias() = x * s;
	}
};

template <typename R, typename X>
struct AddMatrix {
	void operator()(R& r, X& x) {
		r += x;
	}
};

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __Dot
 * Signature: (Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;I)D
 */
JNIEXPORT jdouble JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1Dot(JNIEnv *env, jclass klass, jobject v1_buf, jobject v2_buf, jint size)
{
	DenseVector v1(GetBufferPointer(env, v1_buf, 0), size);
	DenseVector v2(GetBufferPointer(env, v2_buf, 0), size);
	return v1.transpose() * v2;
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AssignMultiplyMatrixMatrixScaler
 * Signature: (Ljava/nio/ByteBuffer;ZLjava/nio/ByteBuffer;ZLjava/nio/ByteBuffer;ZDIII)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AssignMultiplyMatrixMatrixScaler(JNIEnv *env,
		jclass klass,
		jobject r_buf, jboolean r_row_major,
		jobject x_buf, jboolean x_row_major,
		jobject y_buf, jboolean y_row_major,
		jdouble s,
		jint r_rows, jint r_columns, jint k)
{
	JavaDenseMatrix r(GetBufferPointer(env, r_buf, 0), r_rows, r_columns, r_row_major);
	JavaDenseMatrix x(GetBufferPointer(env, x_buf, 0), r_rows, k, x_row_major);
	JavaDenseMatrix y(GetBufferPointer(env, y_buf, 0), k, r_columns, y_row_major);
	call<AssignMultiplyMatrixMatrixScaler>(r, x, y, s);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AssignMultiplyMatrixMatrix
 * Signature: (Ljava/nio/ByteBuffer;ZLjava/nio/ByteBuffer;ZLjava/nio/ByteBuffer;ZIII)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AssignMultiplyMatrixMatrix(JNIEnv *env,
		jclass klass,
		jobject r_buf, jboolean r_row_major,
		jobject x_buf, jboolean x_row_major,
		jobject y_buf, jboolean y_row_major,
		jint r_rows, jint r_columns, jint k)
{
	JavaDenseMatrix r(GetBufferPointer(env, r_buf, 0), r_rows, r_columns, r_row_major);
	JavaDenseMatrix x(GetBufferPointer(env, x_buf, 0), r_rows, k, x_row_major);
	JavaDenseMatrix y(GetBufferPointer(env, y_buf, 0), k, r_columns, y_row_major);
	call<AssignMultiplyMatrixMatrix>(r, x, y);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AssignMultiplyMatrixVector
 * Signature: (Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;ZLjava/nio/ByteBuffer;II)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AssignMultiplyMatrixVector(JNIEnv *env,
		jclass klass,
		jobject r_buf,
		jobject x_buf, jboolean x_row_major,
		jobject y_buf,
		jint r_rows, jint k)
{
	double *x_ptr = GetBufferPointer(env, x_buf, 0);
	DenseVector r(GetBufferPointer(env, r_buf, 0), r_rows);
	DenseVector y(GetBufferPointer(env, y_buf, 0), k);

	// FIXME: use template to handle all cases
	if (x_row_major) {
		DenseRowAligned x(x_ptr, r_rows, k);
		r.noalias() = x * y;
	} else {
		DenseColAligned x(x_ptr, r_rows, k);
		r.noalias() = x * y;
	}
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AssignZeroVector
 * Signature: (Ljava/nio/ByteBuffer;I)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AssignZeroVector(JNIEnv *env, jclass klass, jobject v_buf, jint position, jint size)
{
	DenseVector v(GetBufferPointer(env, v_buf, position), size);
	v.setZero();
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AssignZeroMatrix
 * Signature: (Ljava/nio/ByteBuffer;ZII)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AssignZeroMatrix(JNIEnv *env, jclass klass, jobject m_buf, jboolean m_row_major, jint m_rows, jint m_columns)
{
	JavaDenseMatrix m(GetBufferPointer(env, m_buf, 0), m_rows, m_columns, m_row_major);
	call<AssignZeroMatrix>(m);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AssignMultiplyMatrixScaler
 * Signature: (Ljava/nio/ByteBuffer;ZLjava/nio/ByteBuffer;ZDII)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AssignMultiplyMatrixScaler(JNIEnv *env, jclass klass,
		jobject r_buf, jboolean r_row_major,
		jobject x_buf, jboolean x_row_major,
		jdouble s,
		jint r_rows, jint r_columns)
{
	JavaDenseMatrix r(GetBufferPointer(env, r_buf, 0), r_rows, r_columns, r_row_major);
	JavaDenseMatrix x(GetBufferPointer(env, x_buf, 0), r_rows, r_columns, x_row_major);
	call<AssignMultiplyMatrixScaler>(r, x, s);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AddMultiplyMatrixScaler
 * Signature: (Ljava/nio/ByteBuffer;ZLjava/nio/ByteBuffer;ZDII)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AddMultiplyMatrixScaler(JNIEnv *env, jclass,
		jobject r_buf, jboolean r_row_major,
		jobject x_buf, jboolean x_row_major,
		jdouble s,
		jint r_rows, jint r_columns)
{
	JavaDenseMatrix r(GetBufferPointer(env, r_buf, 0), r_rows, r_columns, r_row_major);
	JavaDenseMatrix x(GetBufferPointer(env, x_buf, 0), r_rows, r_columns, x_row_major);
	call<AddMultiplyMatrixScaler>(r, x, s);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AddMultiplyMatrixMatrixScaler
 * Signature: (Ljava/nio/ByteBuffer;ZLjava/nio/ByteBuffer;ZLjava/nio/ByteBuffer;ZDIII)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AddMultiplyMatrixMatrixScaler(JNIEnv *env, jclass,
		jobject r_buf, jboolean r_row_major,
		jobject x_buf, jboolean x_row_major,
		jobject y_buf, jboolean y_row_major,
		jdouble s,
		jint r_rows, jint r_columns, jint k)
{
	JavaDenseMatrix r(GetBufferPointer(env, r_buf, 0), r_rows, r_columns, r_row_major);
	JavaDenseMatrix x(GetBufferPointer(env, x_buf, 0), r_rows, k, x_row_major);
	JavaDenseMatrix y(GetBufferPointer(env, y_buf, 0), k, r_columns, y_row_major);
	call<AddMultiplyMatrixMatrixScaler>(r, x, y, s);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AddMatrix
 * Signature: (Ljava/nio/ByteBuffer;ZLjava/nio/ByteBuffer;ZII)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AddMatrix(JNIEnv *env, jclass klass,
		jobject r_buf, jboolean r_row_major,
		jobject x_buf, jboolean x_row_major,
		jint r_rows, jint r_columns)
{
	JavaDenseMatrix r(GetBufferPointer(env, r_buf, 0), r_rows, r_columns, r_row_major);
	JavaDenseMatrix x(GetBufferPointer(env, x_buf, 0), r_rows, r_columns, x_row_major);
	call<AddMatrix>(r, x);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __CopyElements
 * Signature: (Ljava/nio/ByteBuffer;ILjava/nio/ByteBuffer;II)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1CopyElements(JNIEnv *env, jclass klass,
		jobject dest_buf, jint dest_index,
		jobject src_buf, jint src_index,
		jint count)
{
	double *dest_ptr = GetBufferPointer(env, dest_buf, 0) + dest_index;
	double *src_ptr = GetBufferPointer(env, src_buf, 0) + src_index;
	for (int i = 0; i < count; ++i)
		*dest_ptr++ = *src_ptr++;
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __L1Norm
 * Signature: (Ljava/nio/ByteBuffer;ZII)D
 */
JNIEXPORT jdouble JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1L1Norm(JNIEnv *env, jclass klass,
		jobject buf, jboolean row_major, jint rows, jint columns)
{
	double *ptr = GetBufferPointer(env, buf, 0);
	if (row_major) {
		DenseRowAligned m(ptr, rows, columns);
		return m.lpNorm<1>();
	} else {
		DenseColAligned m(ptr, rows, columns);
		return m.lpNorm<1>();
	}
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __L2Norm
 * Signature: (Ljava/nio/ByteBuffer;ZII)D
 */
JNIEXPORT jdouble JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1L2Norm(JNIEnv *env, jclass klass,
		jobject buf, jboolean row_major, jint rows, jint columns)
{
	double *ptr = GetBufferPointer(env, buf, 0);
	if (row_major) {
		DenseRowAligned m(ptr, rows, columns);
		return m.lpNorm<2>();
	} else {
		DenseColAligned m(ptr, rows, columns);
		return m.lpNorm<2>();
	}
}
