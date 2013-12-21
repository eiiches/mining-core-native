#include <jni.h>
#include <stdio.h>
#include <Eigen/Core>

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	Eigen::initParallel();
	return JNI_VERSION_1_6;
}
