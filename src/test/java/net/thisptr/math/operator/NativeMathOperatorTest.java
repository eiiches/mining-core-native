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
		final Matrix x = new DenseByteBufferMatrix(new double[][] { { 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } });
		final Vector y = new DenseByteBufferVector(new double[] { 1.0, 2.0, 3.0 });

		sut.assignMultiply(r, x, y);

		assertEquals(1.0, r.get(0), eps);
		assertEquals(3.0, r.get(1), eps);
	}

	@Test
	public void test__AssignMultiplyMatrixScaler() {
		final Matrix r = new DenseByteBufferMatrix(2, 1);
		final Matrix x = new DenseByteBufferMatrix(new double[][] { { 1.0 }, { 2.0 } });

		sut.assignMultiply(r, x, 2.0);

		assertEquals(2.0, r.get(0, 0), eps);
		assertEquals(4.0, r.get(1, 0), eps);
	}

	@Test
	public void test__AssignZeroMatrix() {
		final Matrix r = new DenseByteBufferMatrix(new double[][] { { 1.0 }, { 2.0 } });

		sut.assignZero(r);

		assertEquals(0.0, r.get(0, 0), eps);
		assertEquals(0.0, r.get(1, 0), eps);
	}

	@Test
	public void test__AssignZeroVector() {
		final Vector v = new DenseByteBufferVector(new double[] { 1.0, 2.0 });

		sut.assignZero(v);

		assertEquals(0.0, v.get(0), eps);
		assertEquals(0.0, v.get(1), eps);
	}

	@Test
	public void test__AddMultiplyMatrixScaler() {
		final Matrix r = new DenseByteBufferMatrix(new double[][] { { 1.0 }, { 2.0 } });
		final Matrix x = new DenseByteBufferMatrix(new double[][] { { 1.0 }, { 2.0 } });

		sut.addMultiply(r, x, 2.0);

		assertEquals(3.0, r.get(0, 0), eps);
		assertEquals(6.0, r.get(1, 0), eps);
	}

	@Test
	public void test__AddMultiplyMatrixMatrixScaler() {
		final Matrix r = new DenseByteBufferMatrix(new double[][] { { 1.0 }, { 2.0 } });
		final Matrix x = new DenseByteBufferMatrix(new double[][] { { 1.0, -1.0 }, { 2.0, 1.0 } });
		final Matrix y = new DenseByteBufferMatrix(new double[][] { { 1.0 }, { 2.0 } });

		sut.addMultiply(r, x, y, 2.0);

		assertEquals(-1.0, r.get(0, 0), eps);
		assertEquals(10.0, r.get(1, 0), eps);
	}

	@Test
	public void test_Add() {
		final Matrix r = new DenseByteBufferMatrix(new double[][] { { 1.0 }, { 2.0 } });
		final Matrix x = new DenseByteBufferMatrix(new double[][] { { 1.0 }, { 2.0 } });

		sut.add(r, x);

		assertEquals(2.0, r.get(0, 0), eps);
		assertEquals(4.0, r.get(1, 0), eps);
	}

	@Test
	public void test_CopyElements() {
		final Vector dest = new DenseByteBufferVector(3);
		final Vector src = new DenseByteBufferVector(new double[] { 1, 2, 3, 4 });

		sut.copyElements(dest, 0, src, 1, 3);

		assertEquals(2, dest.get(0), eps);
		assertEquals(3, dest.get(1), eps);
		assertEquals(4, dest.get(2), eps);
	}
}
