package net.thisptr.math.factory;

import net.thisptr.math.matrix.DenseByteBufferMatrix;
import net.thisptr.math.matrix.Matrix;
import net.thisptr.math.operator.MathOperator;
import net.thisptr.math.operator.NativeMathOperator;
import net.thisptr.math.vector.DenseByteBufferVector;
import net.thisptr.math.vector.Vector;

public class NativeMathFactory implements MathFactory {
	@Override
	public Matrix newDenseMatrix(final int rows, final int columns) {
		return new DenseByteBufferMatrix(rows, columns);
	}

	@Override
	public Vector newDenseVector(final int size) {
		return new DenseByteBufferVector(size);
	}

	@Override
	public Vector newSparseVector(final int size) {
		throw new UnsupportedOperationException();
	}

	@Override
	public Matrix newSparseMatrix(final int rows, final int columns) {
		throw new UnsupportedOperationException();
	}

	@Override
	public MathOperator newMathOperator() {
		return new NativeMathOperator();
	}
}
