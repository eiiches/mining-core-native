package net.thisptr.math.operator;

import static org.junit.Assert.assertEquals;
import net.thisptr.math.matrix.DenseArrayMatrix;
import net.thisptr.math.matrix.DenseByteBufferMatrix;
import net.thisptr.math.matrix.Matrix;
import net.thisptr.math.vector.DenseArrayVector;
import net.thisptr.math.vector.DenseByteBufferVector;

import org.junit.Ignore;
import org.junit.Test;

public class NativeMathOperatorPerfTest {
	private static final int N = 10;

	private MathOperator sut = new NativeMathOperator();

	@Test
	@Ignore
	public void testDot() {
		final DenseByteBufferVector v1 = new DenseByteBufferVector(5000000);
		final DenseByteBufferVector v2 = new DenseByteBufferVector(5000000);
		v1.set(1, 1.0);
		v2.set(1, 1.0);

		final long start = System.currentTimeMillis();

		double v = 0;
		for (int i = 0; i < N; ++i)
			v += sut.dot(v1, v2);
		assertEquals(N, v, 0.0001);

		final long end = System.currentTimeMillis();

		System.out.printf("Time(Native): %d msec%n", end - start);
	}

	@Test
	@Ignore
	public void testAssignMultiply() {
		final Matrix x = new DenseByteBufferMatrix(10, 9945);
		final Matrix w = new DenseByteBufferMatrix(9945, 512);
		final Matrix h = new DenseByteBufferMatrix(10, 512);

		final long start = System.currentTimeMillis();

		for (int i = 0; i < N; ++i)
			sut.assignMultiply(h, x, w);

		final long end = System.currentTimeMillis();
		System.out.printf("Time(Native): %d msec%n", end - start);
	}

	@Test
	@Ignore
	public void testAssignMultiplyJava() {
		final DenseArrayMatrix x = new DenseArrayMatrix(10, 9945);
		final DenseArrayMatrix w = new DenseArrayMatrix(9945, 512);
		final DenseArrayMatrix h = new DenseArrayMatrix(10, 512);

		final long start = System.currentTimeMillis();

		for (int i = 0; i < N; ++i)
			MatrixOp.assign_X_Y(h.raw(), x.raw(), w.raw(), null, 1);

		final long end = System.currentTimeMillis();
		System.out.printf("Time(Java): %d msec%n", end - start);
	}

	@Test
	@Ignore
	public void testDotJava() {
		final DenseArrayVector v1 = new DenseArrayVector(5000000);
		final DenseArrayVector v2 = new DenseArrayVector(5000000);
		v1.set(1, 1.0);
		v2.set(1, 1.0);

		final long start = System.currentTimeMillis();

		double v = 0;
		for (int i = 0; i < N; ++i)
			v += ArrayOp.dot(v1.raw(), v2.raw());
		assertEquals(N, v, 0.0001);

		final long end = System.currentTimeMillis();

		System.out.printf("Time(Java): %d msec%n", end - start);
	}
}
