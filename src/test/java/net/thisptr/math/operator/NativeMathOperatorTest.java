package net.thisptr.math.operator;

import static org.junit.Assert.assertEquals;
import net.thisptr.math.matrix.DenseByteBufferMatrix;
import net.thisptr.math.matrix.Matrix;
import net.thisptr.math.vector.DenseByteBufferVector;
import net.thisptr.math.vector.Vector;

import org.junit.Test;

public class NativeMathOperatorTest {
	private static final double eps = 0.000001;

	private MathOperator sut = new NativeMathOperator(TestMathOperators.nullMathOperator());

	@Test
	public void test__Dot() {
		final Vector v1 = new DenseByteBufferVector(2);
		final Vector v2 = new DenseByteBufferVector(2);
		v1.set(1, 1.0);
		v2.set(1, 1.0);

		assertEquals(1.0, sut.dot(v1, v2), eps);
	}

	@Test
	public void test__AssignMultiplyMatrixMatrix() {
		final Matrix r = new DenseByteBufferMatrix(2, 4);
		final Matrix x = new DenseByteBufferMatrix(2, 3);
		final Matrix y = new DenseByteBufferMatrix(3, 4);
		x.set(0, 0, 1.0);
		y.set(0, 0, 1.0);

		sut.assignMultiply(r, x, y);

		assertEquals(1.0, r.get(0, 0), eps);
		assertEquals(0.0, r.get(1, 0), eps);
	}

	@Test
	public void test__AssignMultiplyMatrixVector() {
		final Vector r = new DenseByteBufferVector(2);
		final Matrix x = new DenseByteBufferMatrix(2, 3);
		final Vector y = new DenseByteBufferVector(3);
		x.set(0, 0, 1.0);
		y.set(0, 1.0);

		sut.assignMultiply(r, x, y);

		assertEquals(1.0, r.get(0), eps);
		assertEquals(0.0, r.get(1), eps);
	}
}
