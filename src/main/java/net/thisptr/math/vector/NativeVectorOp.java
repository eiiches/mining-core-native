package net.thisptr.math.vector;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import net.thisptr.MiningCoreNative;

public class NativeVectorOp {
	static {
		MiningCoreNative.loadLibrary();
	}

	private NativeVectorOp() {
	}

	private static native double dot(final ByteBuffer v1, final ByteBuffer v2, final int size);

	private static void checkByteOrder(final DenseByteBufferVector... vs) {
		final ByteOrder nativeOrder = ByteOrder.nativeOrder();
		for (final DenseByteBufferVector v : vs)
			if (!v.raw().order().equals(nativeOrder))
				throw new IllegalArgumentException("The byte order is not compatible with native code.");
	}

	public static double dot(final DenseByteBufferVector v1, final DenseByteBufferVector v2) {
		checkByteOrder(v1, v2);
		final int size = Math.min(v1.size(), v2.size());
		return dot(v1.raw(), v2.raw(), size);
	}
}