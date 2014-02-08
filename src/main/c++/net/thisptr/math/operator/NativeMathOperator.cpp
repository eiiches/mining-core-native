#include <Eigen/Core>
#include <jni.h>
#include <net_thisptr_math_operator_NativeMathOperator.h>
#include "NativeMathOperator.hpp"

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

template <typename R, typename X, typename Y>
struct AssignMultiplyMatrixVector {
	void operator()(R& r, X& x, Y& y) {
		r.noalias() = x * y;
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

template <typename R, typename M>
struct L1Norm {
	void operator()(double& result, M& m) {
		result = m.template lpNorm<1>();
	}
};

template <typename R, typename M>
struct L2Norm {
	void operator()(double& result, M m) {
		result = m.template lpNorm<2>();
	}
};

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __Dot
 * Signature: (Ljava/nio/ByteBuffer;ILjava/nio/ByteBuffer;II)D
 */
JNIEXPORT jdouble JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1Dot(JNIEnv *env, jclass klass, jobject v1_buf, jint v1_offset, jobject v2_buf, jint v2_offset, jint size)
{
	DenseVector v1(GetBufferPointer(env, v1_buf, v1_offset), size);
	DenseVector v2(GetBufferPointer(env, v2_buf, v2_offset), size);
	return v1.transpose() * v2;
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AssignMultiplyMatrixMatrixScaler
 * Signature: (Ljava/nio/ByteBuffer;IZLjava/nio/ByteBuffer;IZLjava/nio/ByteBuffer;IZDIII)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AssignMultiplyMatrixMatrixScaler(JNIEnv *env,
		jclass klass,
		jobject r_buf, jint r_offset, jboolean r_row_major,
		jobject x_buf, jint x_offset, jboolean x_row_major,
		jobject y_buf, jint y_offset, jboolean y_row_major,
		jdouble s,
		jint r_rows, jint r_columns, jint k)
{
	JavaDenseMatrix r(GetBufferPointer(env, r_buf, r_offset), r_rows, r_columns, r_row_major);
	JavaDenseMatrix x(GetBufferPointer(env, x_buf, x_offset), r_rows, k, x_row_major);
	JavaDenseMatrix y(GetBufferPointer(env, y_buf, y_offset), k, r_columns, y_row_major);
	apply<AssignMultiplyMatrixMatrixScaler>(r, x, y, s);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AssignMultiplyMatrixMatrix
 * Signature: (Ljava/nio/ByteBuffer;IZLjava/nio/ByteBuffer;IZLjava/nio/ByteBuffer;IZIII)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AssignMultiplyMatrixMatrix(JNIEnv *env,
		jclass klass,
		jobject r_buf, jint r_offset, jboolean r_row_major,
		jobject x_buf, jint x_offset, jboolean x_row_major,
		jobject y_buf, jint y_offset, jboolean y_row_major,
		jint r_rows, jint r_columns, jint k)
{
	JavaDenseMatrix r(GetBufferPointer(env, r_buf, r_offset), r_rows, r_columns, r_row_major);
	JavaDenseMatrix x(GetBufferPointer(env, x_buf, x_offset), r_rows, k, x_row_major);
	JavaDenseMatrix y(GetBufferPointer(env, y_buf, y_offset), k, r_columns, y_row_major);
	apply<AssignMultiplyMatrixMatrix>(r, x, y);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AssignMultiplyMatrixVector
 * Signature: (Ljava/nio/ByteBuffer;ILjava/nio/ByteBuffer;IZLjava/nio/ByteBuffer;III)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AssignMultiplyMatrixVector(JNIEnv *env,
		jclass klass,
		jobject r_buf, jint r_offset,
		jobject x_buf, jint x_offset, jboolean x_row_major,
		jobject y_buf, jint y_offset,
		jint r_rows, jint k)
{
	JavaDenseMatrix x(GetBufferPointer(env, x_buf, x_offset), r_rows, k, x_row_major);
	DenseVector r(GetBufferPointer(env, r_buf, r_offset), r_rows);
	DenseVector y(GetBufferPointer(env, y_buf, y_offset), k);
	apply<AssignMultiplyMatrixVector>(r, x, y);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AssignZeroVector
 * Signature: (Ljava/nio/ByteBuffer;II)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AssignZeroVector(JNIEnv *env, jclass klass, jobject v_buf, jint position, jint size)
{
	DenseVector v(GetBufferPointer(env, v_buf, position), size);
	v.setZero();
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AssignZeroMatrix
 * Signature: (Ljava/nio/ByteBuffer;IZII)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AssignZeroMatrix(JNIEnv *env, jclass klass, jobject m_buf, jint m_offset, jboolean m_row_major, jint m_rows, jint m_columns)
{
	JavaDenseMatrix m(GetBufferPointer(env, m_buf, m_offset), m_rows, m_columns, m_row_major);
	apply<AssignZeroMatrix>(m);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AssignMultiplyMatrixScaler
 * Signature: (Ljava/nio/ByteBuffer;IZLjava/nio/ByteBuffer;IZDII)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AssignMultiplyMatrixScaler(JNIEnv *env, jclass klass,
		jobject r_buf, jint r_offset, jboolean r_row_major,
		jobject x_buf, jint x_offset, jboolean x_row_major,
		jdouble s,
		jint r_rows, jint r_columns)
{
	JavaDenseMatrix r(GetBufferPointer(env, r_buf, r_offset), r_rows, r_columns, r_row_major);
	JavaDenseMatrix x(GetBufferPointer(env, x_buf, x_offset), r_rows, r_columns, x_row_major);
	apply<AssignMultiplyMatrixScaler>(r, x, s);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AddMultiplyMatrixScaler
 * Signature: (Ljava/nio/ByteBuffer;IZLjava/nio/ByteBuffer;IZDII)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AddMultiplyMatrixScaler(JNIEnv *env, jclass,
		jobject r_buf, jint r_offset, jboolean r_row_major,
		jobject x_buf, jint x_offset, jboolean x_row_major,
		jdouble s,
		jint r_rows, jint r_columns)
{
	JavaDenseMatrix r(GetBufferPointer(env, r_buf, r_offset), r_rows, r_columns, r_row_major);
	JavaDenseMatrix x(GetBufferPointer(env, x_buf, x_offset), r_rows, r_columns, x_row_major);
	apply<AddMultiplyMatrixScaler>(r, x, s);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AddMultiplyMatrixMatrixScaler
 * Signature: (Ljava/nio/ByteBuffer;IZLjava/nio/ByteBuffer;IZLjava/nio/ByteBuffer;IZDIII)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AddMultiplyMatrixMatrixScaler(JNIEnv *env, jclass,
		jobject r_buf, jint r_offset, jboolean r_row_major,
		jobject x_buf, jint x_offset, jboolean x_row_major,
		jobject y_buf, jint y_offset, jboolean y_row_major,
		jdouble s,
		jint r_rows, jint r_columns, jint k)
{
	JavaDenseMatrix r(GetBufferPointer(env, r_buf, r_offset), r_rows, r_columns, r_row_major);
	JavaDenseMatrix x(GetBufferPointer(env, x_buf, x_offset), r_rows, k, x_row_major);
	JavaDenseMatrix y(GetBufferPointer(env, y_buf, y_offset), k, r_columns, y_row_major);
	apply<AddMultiplyMatrixMatrixScaler>(r, x, y, s);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AddMatrix
 * Signature: (Ljava/nio/ByteBuffer;IZLjava/nio/ByteBuffer;IZII)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AddMatrix(JNIEnv *env, jclass klass,
		jobject r_buf, jint r_offset, jboolean r_row_major,
		jobject x_buf, jint x_offset, jboolean x_row_major,
		jint r_rows, jint r_columns)
{
	JavaDenseMatrix r(GetBufferPointer(env, r_buf, r_offset), r_rows, r_columns, r_row_major);
	JavaDenseMatrix x(GetBufferPointer(env, x_buf, x_offset), r_rows, r_columns, x_row_major);
	apply<AddMatrix>(r, x);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __CopyElements
 * Signature: (Ljava/nio/ByteBuffer;IILjava/nio/ByteBuffer;III)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1CopyElements(JNIEnv *env, jclass klass,
		jobject dest_buf, jint dest_offset, jint dest_index,
		jobject src_buf, jint src_offset, jint src_index,
		jint count)
{
	double *dest_ptr = GetBufferPointer(env, dest_buf, dest_offset) + dest_index;
	double *src_ptr = GetBufferPointer(env, src_buf, src_offset) + src_index;
	for (int i = 0; i < count; ++i)
		*dest_ptr++ = *src_ptr++;
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __L1Norm
 * Signature: (Ljava/nio/ByteBuffer;IZII)D
 */
JNIEXPORT jdouble JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1L1Norm(JNIEnv *env, jclass klass,
		jobject buf, jint offset, jboolean row_major, jint rows, jint columns)
{
	JavaDenseMatrix m(GetBufferPointer(env, buf, offset), rows, columns, row_major);
	double result = 0.0;
	apply<L1Norm>(result, m);
	return result;
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __L2Norm
 * Signature: (Ljava/nio/ByteBuffer;IZII)D
 */
JNIEXPORT jdouble JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1L2Norm(JNIEnv *env, jclass klass,
		jobject buf, jint offset, jboolean row_major, jint rows, jint columns)
{
	JavaDenseMatrix m(GetBufferPointer(env, buf, offset), rows, columns, row_major);
	double result = 0.0;
	apply<L2Norm>(result, m);
	return result;
}
