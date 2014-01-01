#include <jni.h>
#include <net_thisptr_math_operator_NativeMathOperator_Check.h>

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator_Check
 * Method:    alignment16
 * Signature: (Ljava/nio/ByteBuffer;)Z
 */
JNIEXPORT jboolean JNICALL Java_net_thisptr_math_operator_NativeMathOperator_00024Check_alignment16(JNIEnv *env, jclass klass, jobject buf)
{
	return ((long) env->GetDirectBufferAddress(buf) & 0x0f) == 0;
}
