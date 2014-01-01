package net.thisptr.math.operator;

import net.thisptr.math.matrix.Matrix;
import net.thisptr.math.vector.Vector;

public class NullMathOperator implements MathOperator {
	@Override
	public void assignMultiply(Vector result, Matrix x, Vector y) {
		throw new UnsupportedOperationException();
	}

	@Override
	public void assignMultiply(Matrix result, Matrix x, Matrix y) {
		throw new UnsupportedOperationException();
	}

	@Override
	public double dot(Vector v1, Vector v2) {
		throw new UnsupportedOperationException();
	}
}
