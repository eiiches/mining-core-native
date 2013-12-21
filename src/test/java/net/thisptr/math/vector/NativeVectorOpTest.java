package net.thisptr.math.vector;

import static org.junit.Assert.assertEquals;
import net.thisptr.math.vector.DenseByteBufferVector;
import net.thisptr.math.vector.NativeVectorOp;

import org.junit.Test;

public class NativeVectorOpTest {
	@Test
	public void testDot() {
		final DenseByteBufferVector v1 = new DenseByteBufferVector(500);
		final DenseByteBufferVector v2 = new DenseByteBufferVector(500);
		v1.set(1, 1.0);
		v2.set(1, 1.0);

		double v = 0;
		for (int i = 0; i < 10; ++i)
			v += NativeVectorOp.dot(v1, v2);
		assertEquals(10.0, v, 0.0001);
	}
}
