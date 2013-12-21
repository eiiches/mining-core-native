package net.thisptr.nativesupport;

import java.io.IOException;
import java.util.Arrays;
import java.util.List;

public class NarLoader {
	private static final List<String> LINKERS = Arrays.asList("gpp");

	public static void loadClasspathNarLibrary(final String artifactId, final String aol) throws IOException {
		final String PATH = String.format("lib/%s/jni/lib%s.so", aol, artifactId);
		NativeLoader.loadClasspathLibrary(PATH);
	}

	public static void loadClasspathNarLibrary(final String artifactId) {
		final String os = System.getProperty("os.name");
		final String arch = System.getProperty("os.arch");
		for (final String linker : LINKERS) {
			try {
				loadClasspathNarLibrary(artifactId, arch + "-" + os + "-" + linker);
				return;
			} catch (IOException | UnsatisfiedLinkError e) {
				e.printStackTrace();
			}
		}
		throw new UnsatisfiedLinkError();
	}
}