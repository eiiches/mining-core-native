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

	private static double[] V(final double... v) {
		return v;
	}

	private static double[][] M(final double[]... r) {
		return r;
	}

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
		final Matrix r = new DenseByteBufferMatrix(2, 2);
		final Matrix x = new DenseByteBufferMatrix(M(V(2, 3), V(5, 7)));
		final Matrix y = new DenseByteBufferMatrix(M(V(11, 13), V(17, 19)));

		sut.assignMultiply(r, x, y);
		assertEquals(73, r.get(0, 0), eps);
		assertEquals(83, r.get(0, 1), eps);
		assertEquals(174, r.get(1, 0), eps);
		assertEquals(198, r.get(1, 1), eps);
	}

	@Test
	public void test__AssignMultiplyMatrixMatrixScaler() {
		final Matrix r = new DenseByteBufferMatrix(2, 2);
		final Matrix x = new DenseByteBufferMatrix(M(V(2, 3), V(5, 7)));
		final Matrix y = new DenseByteBufferMatrix(M(V(11, 13), V(17, 19)));

		sut.assignMultiply(r, x, y, 2);
		assertEquals(73 * 2, r.get(0, 0), eps);
		assertEquals(83 * 2, r.get(0, 1), eps);
		assertEquals(174 * 2, r.get(1, 0), eps);
		assertEquals(198 * 2, r.get(1, 1), eps);
	}

	@Test
	public void test__AssignMultiplyMatrixMatrixWithTranspose() {
		final Matrix r = new DenseByteBufferMatrix(2, 2);
		final Matrix x = new DenseByteBufferMatrix(M(V(2, 3), V(5, 7)));
		final Matrix y = new DenseByteBufferMatrix(M(V(11, 13), V(17, 19)));

		sut.assignMultiply(r, x.transpose(), y);
		assertEquals(107, r.get(0, 0), eps);
		assertEquals(121, r.get(0, 1), eps);
		assertEquals(152, r.get(1, 0), eps);
		assertEquals(172, r.get(1, 1), eps);
	}

	@Test
	public void test__AssignMultiplyMatrixVector() {
		final Vector r = new DenseByteBufferVector(2);
		final Matrix x = new DenseByteBufferMatrix(M(V(2, 3, 5), V(7, 11, 13)));
		final Vector y = new DenseByteBufferVector(V(17, 19, 23));

		sut.assignMultiply(r, x, y);

		assertEquals(206, r.get(0), eps);
		assertEquals(627, r.get(1), eps);
	}

	@Test
	public void test__AssignMultiplyMatrixVectorWithTranspose() {
		final Vector r = new DenseByteBufferVector(2);
		final Matrix x = new DenseByteBufferMatrix(M(V(2, 3), V(5, 7)));
		final Vector y = new DenseByteBufferVector(V(11, 13));

		sut.assignMultiply(r, x.transpose(), y);

		assertEquals(87, r.get(0), eps);
		assertEquals(124, r.get(1), eps);
	}

	@Test
	public void test__AssignMultiplyMatrixScaler() {
		final Matrix r = new DenseByteBufferMatrix(1, 2);
		final Matrix x = new DenseByteBufferMatrix(M(V(1, 2)));

		sut.assignMultiply(r, x, 2.0);

		assertEquals(2.0, r.get(0, 0), eps);
		assertEquals(4.0, r.get(0, 1), eps);
	}

	@Test
	public void test__AssignZeroMatrix() {
		final Matrix r = new DenseByteBufferMatrix(M(V(1, 2), V(3, 4)));

		sut.assignZero(r);

		assertEquals(0.0, r.get(0, 0), eps);
		assertEquals(0.0, r.get(0, 1), eps);
		assertEquals(0.0, r.get(1, 0), eps);
		assertEquals(0.0, r.get(1, 1), eps);
	}
	
	@Test
	public void test_AssignZeroMatrixRow() {
		final Matrix r = new DenseByteBufferMatrix(M(V(1, 2), V(3, 4)));
		
		sut.assignZero(r.row(1));
		assertEquals(1.0, r.get(0, 0), eps);
		assertEquals(2.0, r.get(0, 1), eps);
		assertEquals(0.0, r.get(1, 0), eps);
		assertEquals(0.0, r.get(1, 1), eps);
	}

	@Test
	public void test__AssignZeroVector() {
		final Vector v = new DenseByteBufferVector(V(1, 2, 3));

		sut.assignZero(v);

		assertEquals(0.0, v.get(0), eps);
		assertEquals(0.0, v.get(1), eps);
		assertEquals(0.0, v.get(2), eps);
	}

	@Test
	public void test__AddMultiplyMatrixScaler() {
		final Matrix r = new DenseByteBufferMatrix(M(V(2, 3)));
		final Matrix x = new DenseByteBufferMatrix(M(V(5, 7)));

		sut.addMultiply(r, x, 2.0);
		assertEquals(12, r.get(0, 0), eps);
		assertEquals(17, r.get(0, 1), eps);
	}

	@Test
	public void test__AddMultiplyMatrixMatrixScalerWithTranspose() {
		final Matrix r = new DenseByteBufferMatrix(M(V(2), V(3)));
		final Matrix x = new DenseByteBufferMatrix(M(V(5, 7), V(11, 13)));
		final Matrix y = new DenseByteBufferMatrix(M(V(17), V(19)));

		sut.addMultiply(r, x.transpose(), y, 2.0);
		assertEquals(590, r.get(0, 0), eps);
		assertEquals(735, r.get(1, 0), eps);
	}

	@Test
	public void test__AddMultiplyMatrixMatrixScaler() {
		final Matrix r = new DenseByteBufferMatrix(M(V(2), V(3)));
		final Matrix x = new DenseByteBufferMatrix(M(V(5, 7), V(11, 13)));
		final Matrix y = new DenseByteBufferMatrix(M(V(17), V(19)));

		sut.addMultiply(r, x, y, 2.0);
		assertEquals(438, r.get(0, 0), eps);
		assertEquals(871, r.get(1, 0), eps);
	}

	@Test
	public void test_AddMatrix() {
		final Matrix r = new DenseByteBufferMatrix(M(V(2, 3), V(5, 7)));
		final Matrix x = new DenseByteBufferMatrix(M(V(11, 13), V(17, 19)));

		sut.add(r, x);

		assertEquals(13, r.get(0, 0), eps);
		assertEquals(16, r.get(0, 1), eps);
		assertEquals(22, r.get(1, 0), eps);
		assertEquals(26, r.get(1, 1), eps);
	}

	@Test
	public void test_CopyElements() {
		final Vector dest = new DenseByteBufferVector(3);
		final Vector src = new DenseByteBufferVector(V(1, 2, 3, 4));

		sut.copyElements(dest, 0, src, 1, 3);

		assertEquals(2, dest.get(0), eps);
		assertEquals(3, dest.get(1), eps);
		assertEquals(4, dest.get(2), eps);
	}

	@Test
	public void test_L1Norm() {
		final Matrix m = new DenseByteBufferMatrix(M(V(1, 2), V(-3, 4)));
		assertEquals(10, sut.l1Norm(m), eps);
	}

	@Test
	public void test_L2Norm() {
		final Matrix m = new DenseByteBufferMatrix(M(V(1, 2), V(-3, 4)));
		assertEquals(Math.sqrt(30), sut.l2Norm(m), eps);
	}
}
