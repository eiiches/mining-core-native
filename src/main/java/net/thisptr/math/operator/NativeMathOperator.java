package net.thisptr.math.operator;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import net.thisptr.MiningCoreNative;
import net.thisptr.math.matrix.DenseByteBufferMatrix;
import net.thisptr.math.matrix.Matrix;
import net.thisptr.math.vector.DenseByteBufferVector;
import net.thisptr.math.vector.Vector;

public class NativeMathOperator implements MathOperator {
	static {
		MiningCoreNative.loadLibrary();
	}

	private MathOperator parent;

	public NativeMathOperator() {
		this(new DefaultMathOperator());
	}

	public NativeMathOperator(final MathOperator parent) {
		this.parent = parent;
	}

	@Override
	public double dot(final Vector v1, final Vector v2) {
		if (v1 instanceof DenseByteBufferVector && v2 instanceof DenseByteBufferVector)
			return dot((DenseByteBufferVector) v1, (DenseByteBufferVector) v2);
		return parent.dot(v1, v2);
	}

	public double dot(final DenseByteBufferVector v1, final DenseByteBufferVector v2) {
		Check.checkDenseByteBufferVector(v1, v2);
		assert v1.size() == v2.size();

		return dot(v1.raw(), v2.raw(), v1.size());
	}

	private static native double dot(final ByteBuffer v1, final ByteBuffer v2, final int size);

	@Override
	public void assignMultiply(final Matrix result, final Matrix x, final Matrix y) {
		if (result instanceof DenseByteBufferMatrix && x instanceof DenseByteBufferMatrix && y instanceof DenseByteBufferMatrix) {
			assignMultiply((DenseByteBufferMatrix) result, (DenseByteBufferMatrix) x, (DenseByteBufferMatrix) y);
			return;
		}
		parent.assignMultiply(result, x, y);
	}

	public void assignMultiply(final DenseByteBufferMatrix result, final DenseByteBufferMatrix x, final DenseByteBufferMatrix y) {
		Check.checkDenseByteBufferMatrix(result, x, y);
		assert result.columns() == y.columns();
		assert result.rows() == x.rows();
		assert x.columns() == y.rows();

		assignMultiplyMatrixMatrix(result.raw(), result.rowMajor(), x.raw(), x.rowMajor(), y.raw(), y.rowMajor(), result.rows(), result.columns(), x.columns());
	}

	private static native void assignMultiplyMatrixMatrix(final ByteBuffer result, final boolean resultRowMajor,
			final ByteBuffer x, final boolean xRowMajor,
			final ByteBuffer y, final boolean yRowMajor,
			final int rows, final int columns, final int k);

	@Override
	public void assignMultiply(final Vector result, final Matrix x, final Vector y) {
		if (result instanceof DenseByteBufferVector && x instanceof DenseByteBufferMatrix && y instanceof DenseByteBufferVector) {
			assignMultiply((DenseByteBufferVector) result, (DenseByteBufferMatrix) x, (DenseByteBufferVector) y);
			return;
		}
		parent.assignMultiply(result, x, y);
	}

	public void assignMultiply(final DenseByteBufferVector result, final DenseByteBufferMatrix x, final DenseByteBufferVector y) {
		Check.checkDenseByteBufferMatrix(x);
		Check.checkDenseByteBufferVector(result, y);
		assert result.size() == x.rows();
		assert x.columns() == y.size();

		assignMultiplyMatrixVector(result.raw(), x.raw(), x.rowMajor(), y.raw(), result.size(), y.size());
	}

	private static native void assignMultiplyMatrixVector(final ByteBuffer result,
			final ByteBuffer x, final boolean xRowMajor,
			final ByteBuffer y,
			int rows, int k);

	private static class Check {
		private static void check(final ByteBuffer buf) {
			if (!buf.isDirect())
				throw new IllegalArgumentException("The vector must be backed by DirectByteBuffer.");
			if (!ByteOrder.nativeOrder().equals(buf.order()))
				throw new IllegalArgumentException("The byte order is not compatible with native code.");
			if (!alignment16(buf))
				throw new IllegalArgumentException("The alignment is not compatible with native code.");
		}

		private static void checkDenseByteBufferMatrix(final DenseByteBufferMatrix... ms) {
			for (final DenseByteBufferMatrix m : ms)
				check(m.raw());
		}

		private static void checkDenseByteBufferVector(final DenseByteBufferVector... vs) {
			for (final DenseByteBufferVector v : vs)
				check(v.raw());
		}

		private static native boolean alignment16(final ByteBuffer buf);
	}
}
