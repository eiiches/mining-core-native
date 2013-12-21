#include <jni.h>
#include <net_thisptr_math_vector_NativeVectorOp.h>
#include <Eigen/Core>
#include <iostream>

/*
 * Class:     net_thisptr_math_vector_NativeVectorOp
 * Method:    dot
 * Signature: (Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;I)D
 */
JNIEXPORT jdouble JNICALL Java_net_thisptr_math_vector_NativeVectorOp_dot(JNIEnv *env, jclass klass, jobject b1, jobject b2, jint size)
{
	const jbyte *p1 = (jbyte*) env->GetDirectBufferAddress(b1);
	const jbyte *p2 = (jbyte*) env->GetDirectBufferAddress(b2);
	const Eigen::Map<const Eigen::VectorXd> v1((const jdouble *) p1, size);
	const Eigen::Map<const Eigen::VectorXd> v2((const jdouble *) p2, size);
	return v1.transpose() * v2;
}
