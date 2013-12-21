package net.thisptr.nativesupport;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URL;
import java.util.Enumeration;
import java.util.LinkedHashSet;

public class NativeLoader {
	private NativeLoader() {
	}

	public static LinkedHashSet<URL> findLibrary(final String path) throws IOException {
		final ClassLoader classLoader = NativeLoader.class.getClassLoader();
		final Enumeration<URL> iter = classLoader == null ? ClassLoader.getSystemResources(path) : classLoader.getResources(path);

		final LinkedHashSet<URL> result = new LinkedHashSet<>();
		while (iter.hasMoreElements())
			result.add((URL) iter.nextElement());
		return result;
	}

	public static void copy(final InputStream is, final OutputStream os) throws IOException {
		final byte[] buf = new byte[1024];

		int len = 0;
		while ((len = is.read(buf)) != -1) {
			os.write(buf, 0, len);
		}
	}

	public static void loadClasspathLibrary(final String path) throws IOException {
		final LinkedHashSet<URL> urls = findLibrary(path);
		if (urls.isEmpty())
			throw new UnsatisfiedLinkError("no " + path + " in classpath");
		final URL url = urls.iterator().next();

		final File tempFile = File.createTempFile("lib-", ".so");
		tempFile.deleteOnExit();
		try (final OutputStream os = new FileOutputStream(tempFile)) {
			try (final InputStream is = url.openStream()) {
				copy(is, os);
			}
		}

		System.load(tempFile.getAbsolutePath());
	}
}