#include <jni.h>
#include <net_thisptr_math_operator_NativeMathOperator_Check.h>

/*
 * Class:     net_thisptr_math_operator_NativeMathOperator_Check
 * Method:    alignment16
 * Signature: (Ljava/nio/ByteBuffer;I)Z
 */
JNIEXPORT jboolean JNICALL Java_net_thisptr_math_operator_NativeMathOperator_00024Check_alignment16(JNIEnv *env, jclass klass, jobject buf, jint position)
{
	return ((long) (env->GetDirectBufferAddress(buf) + position) & 0x0f) == 0;
}
