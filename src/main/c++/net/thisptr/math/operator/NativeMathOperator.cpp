#include <jni.h>
#include <net_thisptr_math_operator_NativeMathOperator.h>
#include <Eigen/Core>

typedef typename Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> DenseByteBufferMatrix;
typedef typename Eigen::VectorXd DenseByteBufferVector;

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    dot
 * Signature: (Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;I)D
 */
JNIEXPORT jdouble JNICALL Java_net_thisptr_math_operator_NativeMathOperator_dot(JNIEnv *env, jclass klass, jobject v1_buf, jobject v2_buf, jint size)
{
	Eigen::Map<const DenseByteBufferVector, Eigen::Aligned> v1((double *) env->GetDirectBufferAddress(v1_buf), size);
	Eigen::Map<const DenseByteBufferVector, Eigen::Aligned> v2((double *) env->GetDirectBufferAddress(v2_buf), size);
	return v1.transpose() * v2;
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    assignMultiplyMatrixMatrix
 * Signature: (Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;III)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator_assignMultiplyMatrixMatrix(JNIEnv *env, jclass klass, jobject r_buf, jobject x_buf, jobject y_buf, jint r_rows, jint r_columns, jint k)
{
	Eigen::Map<DenseByteBufferMatrix, Eigen::Aligned> r((double *) env->GetDirectBufferAddress(r_buf), r_rows, r_columns);
	Eigen::Map<const DenseByteBufferMatrix, Eigen::Aligned> x((double *) env->GetDirectBufferAddress(x_buf), r_rows, k);
	Eigen::Map<const DenseByteBufferMatrix, Eigen::Aligned> y((double *) env->GetDirectBufferAddress(y_buf), k, r_columns);
	r.noalias() = x * y;
}

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator
 * Method:    assignMultiplyMatrixVector
 * Signature: (Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;II)V
 */
JNIEXPORT void JNICALL Java_net_thisptr_math_operator_NativeMathOperator_assignMultiplyMatrixVector(JNIEnv *env, jclass klass, jobject r_buf, jobject x_buf, jobject y_buf, jint r_rows, jint k)
{
	Eigen::Map<DenseByteBufferVector, Eigen::Aligned> r((double *) env->GetDirectBufferAddress(r_buf), r_rows);
	Eigen::Map<const DenseByteBufferMatrix, Eigen::Aligned> x((double *) env->GetDirectBufferAddress(x_buf), r_rows, k);
	Eigen::Map<const DenseByteBufferVector, Eigen::Aligned> y((double *) env->GetDirectBufferAddress(y_buf), k);
	r.noalias() = x * y;
}
