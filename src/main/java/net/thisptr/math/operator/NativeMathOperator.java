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

		return __Dot(v1.raw(), v2.raw(), v1.size());
	}

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

		__AssignMultiplyMatrixMatrix(result.raw(), result.rowMajor(), x.raw(), x.rowMajor(), y.raw(), y.rowMajor(), result.rows(), result.columns(), x.columns());
	}

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

		__AssignMultiplyMatrixVector(result.raw(), x.raw(), x.rowMajor(), y.raw(), result.size(), y.size());
	}

	@Override
	public void assignMultiply(final Matrix result, final Matrix x, final double s) {
		if (result instanceof DenseByteBufferMatrix && x instanceof DenseByteBufferMatrix) {
			assignMultiply((DenseByteBufferMatrix) result, (DenseByteBufferMatrix) x, s);
			return;
		}
		parent.assignMultiply(result, x, s);
	}

	public void assignMultiply(final DenseByteBufferMatrix result, final DenseByteBufferMatrix x, final double s) {
		Check.checkDenseByteBufferMatrix(result, x);
		assert result.rows() == x.rows();
		assert result.columns() == x.columns();

		__AssignMultiplyMatrixScaler(result.raw(), result.rowMajor(), x.raw(), x.rowMajor(), s, result.rows(), result.columns());
	}

	@Override
	public void assignZero(final Vector v) {
		if (v instanceof DenseByteBufferVector) {
			assignZero((DenseByteBufferVector) v);
			return;
		}
		parent.assignZero(v);
	}

	public void assignZero(final DenseByteBufferVector v) {
		Check.checkDenseByteBufferVector(v);

		__AssignZeroVector(v.raw(), v.size());
	}

	@Override
	public void assignZero(final Matrix m) {
		if (m instanceof DenseByteBufferMatrix) {
			assignZero((DenseByteBufferMatrix) m);
			return;
		}
		parent.assignZero(m);
	}

	public void assignZero(final DenseByteBufferMatrix m) {
		Check.checkDenseByteBufferMatrix(m);

		__AssignZeroMatrix(m.raw(), m.rowMajor(), m.rows(), m.columns());
	}

	@Override
	public void addMultiply(final Matrix self, final Matrix x, final double s) {
		if (self instanceof DenseByteBufferMatrix && x instanceof DenseByteBufferMatrix) {
			addMultiply((DenseByteBufferMatrix) self, (DenseByteBufferMatrix) x, s);
			return;
		}
		parent.addMultiply(self, x, s);
	}

	public void addMultiply(final DenseByteBufferMatrix self, final DenseByteBufferMatrix x, final double s) {
		Check.checkDenseByteBufferMatrix(self, x);
		assert self.rows() == x.rows();
		assert self.columns() == x.columns();

		__AddMultiplyMatrixScaler(self.raw(), self.rowMajor(), x.raw(), x.rowMajor(), s, self.rows(), self.columns());
	}

	@Override
	public void addMultiply(final Matrix self, final Matrix x, final Matrix y, final double s) {
		if (self instanceof DenseByteBufferMatrix && x instanceof DenseByteBufferMatrix && y instanceof DenseByteBufferMatrix) {
			addMultiply((DenseByteBufferMatrix) self, (DenseByteBufferMatrix) x, (DenseByteBufferMatrix) y, s);
			return;
		}
		parent.addMultiply(self, x, y, s);
	}

	public void addMultiply(final DenseByteBufferMatrix self, final DenseByteBufferMatrix x, final DenseByteBufferMatrix y, final double s) {
		Check.checkDenseByteBufferMatrix(self, x, y);
		assert self.rows() == x.rows();
		assert self.columns() == y.columns();
		assert x.columns() == y.rows();

		__AddMultiplyMatrixMatrixScaler(self.raw(), self.rowMajor(), x.raw(), x.rowMajor(), y.raw(), y.rowMajor(), s, self.rows(), self.columns(), x.columns());
	}

	@Override
	public void add(final Matrix self, final Matrix x) {
		if (self instanceof DenseByteBufferMatrix && x instanceof DenseByteBufferMatrix) {
			add((DenseByteBufferMatrix) self, (DenseByteBufferMatrix) x);
			return;
		}
		parent.add(self, x);
	}

	public void add(final DenseByteBufferMatrix self, final DenseByteBufferMatrix x) {
		Check.checkDenseByteBufferMatrix(self, x);
		assert self.rows() == x.rows();
		assert self.columns() == x.columns();

		__AddMatrix(self.raw(), self.rowMajor(), x.raw(), x.rowMajor(), self.rows(), self.columns());
	}

	@Override
	public void copyElements(final Vector dest, final int destIndex, final Vector src, final int srcIndex, final int count) {
		if (dest instanceof DenseByteBufferVector && src instanceof DenseByteBufferVector) {
			copyElements((DenseByteBufferVector) dest, destIndex, (DenseByteBufferVector) src, srcIndex, count);
			return;
		}
		parent.copyElements(dest, destIndex, src, srcIndex, count);
	}

	public void copyElements(final DenseByteBufferVector dest, final int destIndex, final DenseByteBufferVector src, final int srcIndex, final int count) {
		Check.checkDenseByteBufferVector(dest, src);

		__CopyElements(dest.raw(), destIndex, src.raw(), srcIndex, count);
	}

	private static native void __CopyElements(final ByteBuffer dest, final int destIndex, final ByteBuffer src, final int srcIndex, final int count);

	private static native double __Dot(final ByteBuffer v1, final ByteBuffer v2, final int size);

	private static native void __AssignMultiplyMatrixMatrix(final ByteBuffer result, final boolean resultRowMajor,
			final ByteBuffer x, final boolean xRowMajor,
			final ByteBuffer y, final boolean yRowMajor,
			final int rows, final int columns, final int k);

	private static native void __AssignMultiplyMatrixVector(final ByteBuffer result,
			final ByteBuffer x, final boolean xRowMajor,
			final ByteBuffer y,
			int rows, int k);

	private static native void __AssignMultiplyMatrixScaler(final ByteBuffer result, boolean resultRowMajor,
			final ByteBuffer x, boolean xRowMajor,
			double s,
			int rows, int columns);

	private static native void __AssignZeroVector(final ByteBuffer result, final int size);

	private static native void __AssignZeroMatrix(final ByteBuffer result, final boolean rowMajor, final int rows, final int columns);

	private static native void __AddMultiplyMatrixScaler(final ByteBuffer self, final boolean selfRowMajor,
			final ByteBuffer x, final boolean xRowMajor,
			final double s,
			final int rows, final int columns);

	private static native void __AddMultiplyMatrixMatrixScaler(final ByteBuffer self, final boolean selfRowMajor,
			final ByteBuffer x, final boolean xRowMajor,
			final ByteBuffer y, final boolean yRowMajor,
			final double s,
			final int rows, final int columns, final int k);

	private static native void __AddMatrix(final ByteBuffer self, final boolean selfRowMajor,
			final ByteBuffer x, final boolean xRowMajor,
			final int rows, final int columns);

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
