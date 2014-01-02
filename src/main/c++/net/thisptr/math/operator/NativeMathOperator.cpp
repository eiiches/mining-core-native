#include <jni.h>
#include <net_thisptr_math_operator_NativeMathOperator.h>
#include <Eigen/Core>

typedef typename Eigen::Map<Eigen::VectorXd, Eigen::Aligned> DenseVector;
typedef typename Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>, Eigen::Aligned> DenseRowMatrix;
typedef typename Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>, Eigen::Aligned> DenseColMatrix;

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __Dot
 * Signature: (Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;I)D
 */
JNIEXPORT jdouble JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1Dot(JNIEnv *env, jclass klass, jobject v1_buf, jobject v2_buf, jint size)
{
	DenseVector v1((double *) env->GetDirectBufferAddress(v1_buf), size);
	DenseVector v2((double *) env->GetDirectBufferAddress(v2_buf), size);
	return v1.transpose() * v2;
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
	double *r_ptr = (double *) env->GetDirectBufferAddress(r_buf);
	double *x_ptr = (double *) env->GetDirectBufferAddress(x_buf);
	double *y_ptr = (double *) env->GetDirectBufferAddress(y_buf);

	DenseRowMatrix r(r_ptr, r_rows, r_columns);
	DenseRowMatrix x(x_ptr, r_rows, k);
	DenseRowMatrix y(y_ptr, k, r_columns);

	if (r_row_major) {
		DenseRowMatrix r(r_ptr, r_rows, r_columns);
		if (x_row_major) {
			DenseRowMatrix x(x_ptr, r_rows, k);
			if (y_row_major) {
				DenseRowMatrix y(y_ptr, k, r_columns);
				r.noalias() = x * y;
			} else {
				DenseColMatrix y(y_ptr, k, r_columns);
				r.noalias() = x * y;
			}
		} else {
			DenseColMatrix x(x_ptr, r_rows, k);
			if (y_row_major) {
				DenseRowMatrix y(y_ptr, k, r_columns);
				r.noalias() = x * y;
			} else {
				DenseColMatrix y(y_ptr, k, r_columns);
				r.noalias() = x * y;
			}
		}
	} else {
		DenseColMatrix r(r_ptr, r_rows, r_columns);
		if (x_row_major) {
			DenseRowMatrix x(x_ptr, r_rows, k);
			if (y_row_major) {
				DenseRowMatrix y(y_ptr, k, r_columns);
				r.noalias() = x * y;
			} else {
				DenseColMatrix y(y_ptr, k, r_columns);
				r.noalias() = x * y;
			}
		} else {
			DenseColMatrix x(x_ptr, r_rows, k);
			if (y_row_major) {
				DenseRowMatrix y(y_ptr, k, r_columns);
				r.noalias() = x * y;
			} else {
				DenseColMatrix y(y_ptr, k, r_columns);
				r.noalias() = x * y;
			}
		}
	}
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
	double *x_ptr = (double *) env->GetDirectBufferAddress(x_buf);
	DenseVector r((double *) env->GetDirectBufferAddress(r_buf), r_rows);
	DenseVector y((double *) env->GetDirectBufferAddress(y_buf), k);

	// FIXME: use template to handle all cases
	if (x_row_major) {
		DenseRowMatrix x(x_ptr, r_rows, k);
		r.noalias() = x * y;
	} else {
		DenseColMatrix x(x_ptr, r_rows, k);
		r.noalias() = x * y;
	}
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AssignZeroVector
 * Signature: (Ljava/nio/ByteBuffer;I)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AssignZeroVector(JNIEnv *env, jclass klass, jobject v_buf, jint size)
{
	DenseVector v((double *) env->GetDirectBufferAddress(v_buf), size);
	v = DenseVector::Zero(size);
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    __AssignZeroMatrix
 * Signature: (Ljava/nio/ByteBuffer;ZII)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator__1_1AssignZeroMatrix(JNIEnv *env, jclass klass, jobject m_buf, jboolean m_row_major, jint m_rows, jint m_columns)
{
	double *m_ptr = (double *) env->GetDirectBufferAddress(m_buf);
	if (m_row_major) {
		DenseRowMatrix m(m_ptr, m_rows, m_columns);
		m = DenseRowMatrix::Zero(m_rows, m_columns);
	} else {
		DenseColMatrix m(m_ptr, m_rows, m_columns);
		m = DenseColMatrix::Zero(m_rows, m_columns);
	}
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
	double *r_ptr = (double *) env->GetDirectBufferAddress(r_buf);
	double *x_ptr = (double *) env->GetDirectBufferAddress(x_buf);

	// FIXME: use template...
	if (r_row_major) {
		DenseRowMatrix r(r_ptr, r_rows, r_columns);
		if (x_row_major) {
			DenseRowMatrix x(x_ptr, r_rows, r_columns);
			r.noalias() = x * s;
		} else {
			DenseColMatrix x(x_ptr, r_rows, r_columns);
			r.noalias() = x * s;
		}
	} else {
		DenseColMatrix r(r_ptr, r_rows, r_columns);
		if (x_row_major) {
			DenseRowMatrix x(x_ptr, r_rows, r_columns);
			r.noalias() = x * s;
		} else {
			DenseColMatrix x(x_ptr, r_rows, r_columns);
			r.noalias() = x * s;
		}
	}
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
	double *r_ptr = (double *) env->GetDirectBufferAddress(r_buf);
	double *x_ptr = (double *) env->GetDirectBufferAddress(x_buf);

	// FIXME: use template...
	if (r_row_major) {
		DenseRowMatrix r(r_ptr, r_rows, r_columns);
		if (x_row_major) {
			DenseRowMatrix x(x_ptr, r_rows, r_columns);
			r.noalias() += x * s;
		} else {
			DenseColMatrix x(x_ptr, r_rows, r_columns);
			r.noalias() += x * s;
		}
	} else {
		DenseColMatrix r(r_ptr, r_rows, r_columns);
		if (x_row_major) {
			DenseRowMatrix x(x_ptr, r_rows, r_columns);
			r.noalias() += x * s;
		} else {
			DenseColMatrix x(x_ptr, r_rows, r_columns);
			r.noalias() += x * s;
		}
	}
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
	double *r_ptr = (double *) env->GetDirectBufferAddress(r_buf);
	double *x_ptr = (double *) env->GetDirectBufferAddress(x_buf);
	double *y_ptr = (double *) env->GetDirectBufferAddress(y_buf);

	if (r_row_major) {
		DenseRowMatrix r(r_ptr, r_rows, r_columns);
		if (x_row_major) {
			DenseRowMatrix x(x_ptr, r_rows, k);
			if (y_row_major) {
				DenseRowMatrix y(y_ptr, k, r_columns);
				r.noalias() += x * y * s;
			} else {
				DenseColMatrix y(y_ptr, k, r_columns);
				r.noalias() += x * y * s;
			}
		} else {
			DenseColMatrix x(x_ptr, r_rows, k);
			if (y_row_major) {
				DenseRowMatrix y(y_ptr, k, r_columns);
				r.noalias() += x * y * s;
			} else {
				DenseColMatrix y(y_ptr, k, r_columns);
				r.noalias() += x * y * s;
			}
		}
	} else {
		DenseColMatrix r(r_ptr, r_rows, r_columns);
		if (x_row_major) {
			DenseRowMatrix x(x_ptr, r_rows, k);
			if (y_row_major) {
				DenseRowMatrix y(y_ptr, k, r_columns);
				r.noalias() += x * y * s;
			} else {
				DenseColMatrix y(y_ptr, k, r_columns);
				r.noalias() += x * y * s;
			}
		} else {
			DenseColMatrix x(x_ptr, r_rows, k);
			if (y_row_major) {
				DenseRowMatrix y(y_ptr, k, r_columns);
				r.noalias() += x * y * s;
			} else {
				DenseColMatrix y(y_ptr, k, r_columns);
				r.noalias() += x * y * s;
			}
		}
	}
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
	double *r_ptr = (double *) env->GetDirectBufferAddress(r_buf);
	double *x_ptr = (double *) env->GetDirectBufferAddress(x_buf);

	// FIXME: use template...
	if (r_row_major) {
		DenseRowMatrix r(r_ptr, r_rows, r_columns);
		if (x_row_major) {
			DenseRowMatrix x(x_ptr, r_rows, r_columns);
			r += x;
		} else {
			DenseColMatrix x(x_ptr, r_rows, r_columns);
			r += x;
		}
	} else {
		DenseColMatrix r(r_ptr, r_rows, r_columns);
		if (x_row_major) {
			DenseRowMatrix x(x_ptr, r_rows, r_columns);
			r += x;
		} else {
			DenseColMatrix x(x_ptr, r_rows, r_columns);
			r += x;
		}
	}
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
	double *dest_ptr = ((double *) env->GetDirectBufferAddress(dest_buf)) + dest_index;
	double *src_ptr = ((double *) env->GetDirectBufferAddress(src_buf)) + src_index;
	for (int i = 0; i < count; ++i)
		*dest_ptr++ = *src_ptr++;
}

