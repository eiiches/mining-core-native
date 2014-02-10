package net.thisptr.math.operator;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import net.thisptr.MiningCoreNative;
import net.thisptr.math.matrix.DenseByteBufferMatrix;
import net.thisptr.math.matrix.Matrix;
import net.thisptr.math.matrix.StorageOrder;
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
		if (Check.isNativeCompatible(v1, v2))
			return dot((DenseByteBufferVector) v1, (DenseByteBufferVector) v2);
		return parent.dot(v1, v2);
	}

	public double dot(final DenseByteBufferVector v1, final DenseByteBufferVector v2) {
		assert v1.size() == v2.size();

		return __Dot(v1.raw(), v1.raw().position(), v2.raw(), v2.raw().position(), v1.size());
	}

	@Override
	public void assignMultiply(final Matrix result, final Matrix x, final Matrix y) {
		if (Check.isNativeCompatible(result, x, y)) {
			assignMultiply((DenseByteBufferMatrix) result, (DenseByteBufferMatrix) x, (DenseByteBufferMatrix) y);
			return;
		}
		parent.assignMultiply(result, x, y);
	}

	@Override
	public void assignMultiply(final Matrix result, final Matrix x, final Matrix y, final double s) {
		if (Check.isNativeCompatible(result, x, y)) {
			assignMultiply((DenseByteBufferMatrix) result, (DenseByteBufferMatrix) x, (DenseByteBufferMatrix) y, s);
			return;
		}
		parent.assignMultiply(result, x, y, s);
	}

	public void assignMultiply(final DenseByteBufferMatrix result, final DenseByteBufferMatrix x, final DenseByteBufferMatrix y) {
		assert result.columns() == y.columns();
		assert result.rows() == x.rows();
		assert x.columns() == y.rows();

		__AssignMultiplyMatrixMatrix(result.raw(), result.raw().position(), isRowMajor(result), x.raw(), x.raw().position(), isRowMajor(x), y.raw(), y.raw().position(), isRowMajor(y), result.rows(), result.columns(), x.columns());
	}

	public void assignMultiply(final DenseByteBufferMatrix result, final DenseByteBufferMatrix x, final DenseByteBufferMatrix y, final double s) {
		assert result.columns() == y.columns();
		assert result.rows() == x.rows();
		assert x.columns() == y.rows();

		__AssignMultiplyMatrixMatrixScaler(result.raw(), result.raw().position(), isRowMajor(result), x.raw(), x.raw().position(), isRowMajor(x), y.raw(), y.raw().position(), isRowMajor(y), s, result.rows(), result.columns(), x.columns());
	}

	@Override
	public void assignMultiply(final Vector result, final Matrix x, final Vector y) {
		if (Check.isNativeCompatible(result, x, y)) {
			assignMultiply((DenseByteBufferVector) result, (DenseByteBufferMatrix) x, (DenseByteBufferVector) y);
			return;
		}
		parent.assignMultiply(result, x, y);
	}

	public void assignMultiply(final DenseByteBufferVector result, final DenseByteBufferMatrix x, final DenseByteBufferVector y) {
		assert result.size() == x.rows();
		assert x.columns() == y.size();

		__AssignMultiplyMatrixVector(result.raw(), result.raw().position(), x.raw(), x.raw().position(), isRowMajor(x), y.raw(), y.raw().position(), result.size(), y.size());
	}

	@Override
	public void assignMultiply(final Matrix result, final Matrix x, final double s) {
		if (Check.isNativeCompatible(result, x)) {
			assignMultiply((DenseByteBufferMatrix) result, (DenseByteBufferMatrix) x, s);
			return;
		}
		parent.assignMultiply(result, x, s);
	}

	public void assignMultiply(final DenseByteBufferMatrix result, final DenseByteBufferMatrix x, final double s) {
		assert result.rows() == x.rows();
		assert result.columns() == x.columns();

		__AssignMultiplyMatrixScaler(result.raw(), result.raw().position(), isRowMajor(result), x.raw(), x.raw().position(), isRowMajor(x), s, result.rows(), result.columns());
	}

	@Override
	public void assignZero(final Vector v) {
		if (Check.isNativeCompatible(v)) {
			assignZero((DenseByteBufferVector) v);
			return;
		}
		parent.assignZero(v);
	}

	public void assignZero(final DenseByteBufferVector v) {
		__AssignZeroVector(v.raw(), v.raw().position(), v.size());
	}

	@Override
	public void assignZero(final Matrix m) {
		if (Check.isNativeCompatible(m)) {
			assignZero((DenseByteBufferMatrix) m);
			return;
		}
		parent.assignZero(m);
	}

	public void assignZero(final DenseByteBufferMatrix m) {
		__AssignZeroMatrix(m.raw(), m.raw().position(), isRowMajor(m), m.rows(), m.columns());
	}

	@Override
	public void addMultiply(final Matrix self, final Matrix x, final double s) {
		if (Check.isNativeCompatible(self, x)) {
			addMultiply((DenseByteBufferMatrix) self, (DenseByteBufferMatrix) x, s);
			return;
		}
		parent.addMultiply(self, x, s);
	}

	public void addMultiply(final DenseByteBufferMatrix self, final DenseByteBufferMatrix x, final double s) {
		assert self.rows() == x.rows();
		assert self.columns() == x.columns();

		__AddMultiplyMatrixScaler(self.raw(), self.raw().position(), isRowMajor(self), x.raw(), x.raw().position(), isRowMajor(x), s, self.rows(), self.columns());
	}

	@Override
	public void addMultiply(final Matrix self, final Matrix x, final Matrix y, final double s) {
		if (Check.isNativeCompatible(self, x, y)) {
			addMultiply((DenseByteBufferMatrix) self, (DenseByteBufferMatrix) x, (DenseByteBufferMatrix) y, s);
			return;
		}
		parent.addMultiply(self, x, y, s);
	}

	public void addMultiply(final DenseByteBufferMatrix self, final DenseByteBufferMatrix x, final DenseByteBufferMatrix y, final double s) {
		assert self.rows() == x.rows();
		assert self.columns() == y.columns();
		assert x.columns() == y.rows();

		__AddMultiplyMatrixMatrixScaler(self.raw(), self.raw().position(), isRowMajor(self), x.raw(), x.raw().position(), isRowMajor(x), y.raw(), y.raw().position(), isRowMajor(y), s, self.rows(), self.columns(), x.columns());
	}

	@Override
	public void add(final Matrix self, final Matrix x) {
		if (Check.isNativeCompatible(self, x)) {
			add((DenseByteBufferMatrix) self, (DenseByteBufferMatrix) x);
			return;
		}
		parent.add(self, x);
	}

	private boolean isRowMajor(final DenseByteBufferMatrix m) {
		return m.storageOrder() == StorageOrder.RowMajor;
	}

	public void add(final DenseByteBufferMatrix self, final DenseByteBufferMatrix x) {
		assert self.rows() == x.rows();
		assert self.columns() == x.columns();

		__AddMatrix(self.raw(), self.raw().position(), isRowMajor(self), x.raw(), x.raw().position(), isRowMajor(x), self.rows(), self.columns());
	}

	@Override
	public void copyElements(final Vector dest, final int destIndex, final Vector src, final int srcIndex, final int count) {
		if (Check.isNativeCompatible(dest, src)) {
			copyElements((DenseByteBufferVector) dest, destIndex, (DenseByteBufferVector) src, srcIndex, count);
			return;
		}
		parent.copyElements(dest, destIndex, src, srcIndex, count);
	}

	public void copyElements(final DenseByteBufferVector dest, final int destIndex, final DenseByteBufferVector src, final int srcIndex, final int count) {
		__CopyElements(dest.raw(), dest.raw().position(), destIndex, src.raw(), src.raw().position(), srcIndex, count);
	}

	@Override
	public double l1Norm(final Matrix m) {
		if (Check.isNativeCompatible(m)) {
			final DenseByteBufferMatrix mm = (DenseByteBufferMatrix) m;
			return __L1Norm(mm.raw(), mm.raw().position(), isRowMajor(mm), m.rows(), m.columns());
		}
		return parent.l1Norm(m);
	}

	@Override
	public double l2Norm(Matrix m) {
		if (Check.isNativeCompatible(m)) {
			final DenseByteBufferMatrix mm = (DenseByteBufferMatrix) m;
			return __L2Norm(mm.raw(), mm.raw().position(), isRowMajor(mm), m.rows(), m.columns());
		}
		return parent.l2Norm(m);
	}

	private static native double __L1Norm(final ByteBuffer m, final int position, final boolean rowMajor, final int rows, final int columns);

	private static native double __L2Norm(final ByteBuffer m, final int position, final boolean rowMajor, final int rows, final int columns);

	private static native void __CopyElements(final ByteBuffer dest, final int destPosition, final int destIndex, final ByteBuffer src, final int srcPosition, final int srcIndex, final int count);

	private static native double __Dot(final ByteBuffer v1, final int v1Position, final ByteBuffer v2, final int v2Position, final int size);

	private static native void __AssignMultiplyMatrixMatrix(final ByteBuffer result, final int resultPosition, final boolean resultRowMajor,
			final ByteBuffer x, final int xPosition, final boolean xRowMajor,
			final ByteBuffer y, final int yPosition, final boolean yRowMajor,
			final int rows, final int columns, final int k);

	private static native void __AssignMultiplyMatrixMatrixScaler(final ByteBuffer result, final int resultPosition, final boolean resultRowMajor,
			final ByteBuffer x, final int xPosition, final boolean xRowMajor,
			final ByteBuffer y, final int yPosition, final boolean yRowMajor,
			final double s,
			final int rows, final int columns, final int k);

	private static native void __AssignMultiplyMatrixVector(final ByteBuffer result, final int resultPosition,
			final ByteBuffer x, final int xPosition, final boolean xRowMajor,
			final ByteBuffer y, final int yPosition,
			int rows, int k);

	private static native void __AssignMultiplyMatrixScaler(final ByteBuffer result, final int resultPosition, boolean resultRowMajor,
			final ByteBuffer x, final int xPosition, boolean xRowMajor,
			double s,
			int rows, int columns);

	private static native void __AssignZeroVector(final ByteBuffer result, final int position, final int size);

	private static native void __AssignZeroMatrix(final ByteBuffer result, final int position, final boolean rowMajor, final int rows, final int columns);

	private static native void __AddMultiplyMatrixScaler(final ByteBuffer self, final int position, final boolean selfRowMajor,
			final ByteBuffer x, final int xPosition, final boolean xRowMajor,
			final double s,
			final int rows, final int columns);

	private static native void __AddMultiplyMatrixMatrixScaler(final ByteBuffer self, final int selfPosition, final boolean selfRowMajor,
			final ByteBuffer x, final int xPosition, final boolean xRowMajor,
			final ByteBuffer y, final int yPosition, final boolean yRowMajor,
			final double s,
			final int rows, final int columns, final int k);

	private static native void __AddMatrix(final ByteBuffer self, final int selfPosition, final boolean selfRowMajor,
			final ByteBuffer x, final int xPosition, final boolean xRowMajor,
			final int rows, final int columns);

	private static class Check {
		private static boolean isNativeCompatible(final ByteBuffer buf) {
			if (!buf.isDirect())
				return false;
			if (!ByteOrder.nativeOrder().equals(buf.order()))
				return false;
			return true;
		}

		private static boolean isNativeCompatible(final Matrix... ms) {
			for (final Matrix m : ms) {
				if (m instanceof DenseByteBufferMatrix) {
					if (!isNativeCompatible(((DenseByteBufferMatrix) m).raw()))
						return false;
				} else if (m instanceof DenseByteBufferVector) {
					if (!isNativeCompatible(((DenseByteBufferVector) m).raw()))
						return false;
				} else {
					return false;
				}
			}
			return true;
		}
	}
}
