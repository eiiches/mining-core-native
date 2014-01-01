package net.thisptr.math.operator;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;


public class TestMathOperators {
	public static MathOperator nullMathOperator() {
		return (MathOperator) Proxy.newProxyInstance(TestMathOperators.class.getClassLoader(), new Class[]{ MathOperator.class }, new InvocationHandler() {
			@Override
			public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
				throw new UnsupportedOperationException();
			}
		});
	}
}
