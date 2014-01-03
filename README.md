mining-core-native
==================

A native vector / matrix addition for mining-core, which utilizes [Eigen](http://eigen.tuxfamily.org/) via JNI for faster operation.

WARNING: This library is still in alpha, and the APIs can be drastically changed.

Installation
------------

If you use maven, add the following snippet for your pom.
```xml
<repositories>
	<repository>
		<id>thisptr.net</id>
		<name>thisptr.net</name>
		<url>http://nexus.thisptr.net/content/groups/public</url>
	</repository>
</repositories>
<dependency>
	<groupId>net.thisptr</groupId>
	<artifactId>mining-core-native</artifactId>
	<version>0.0.1-SNAPSHOT</version>
</dependency>
```

Also, to build the native library, clone this repository and execute
```sh
mvn clean package
```
which will generate ${project.build.directory}/mining-core-native-{version}-{arch}-{os}-{linker}-jni.nar. 
You have to add this package to your classpath.
