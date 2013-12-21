package net.thisptr;

import net.thisptr.nativesupport.NarLoader;

public class MiningCoreNative {
	public static void loadLibrary() {
		NarLoader.loadClasspathNarLibrary("mining-core-native");
	}
}
