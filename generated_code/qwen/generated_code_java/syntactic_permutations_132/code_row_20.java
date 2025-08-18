import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorld {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> renderHello(request.params(":username")));
    }

    private static String renderHello(String username) {
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }
}



<!-- hello.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello Page</title>
</head>
<body>
    <h1>Hello, ${username}!</h1>
</body>
</html>


Note: The provided code uses the Spark framework for simplicity. To run this code, you need to add the Spark dependency in your project. Here is how you can do it if you are using Maven:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.4</version>
</dependency>


And here is the complete runnable code including the dependency management with Maven:


import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorld {
    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> renderHello(request.params(":username")));
    }

    private static String renderHello(String username) {
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>HelloWorldApp</groupId>
    <artifactId>HelloWorldApp</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.4</version>
        </dependency>
    </dependencies>
    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <configuration>
                    <source>1.8</source>
                    <target>1.8</target>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>


Please place the `HelloWorld.java` file in the `src/main/java` directory and ensure your project structure follows Maven conventions. The HTML content is provided for reference but is not directly used in this Java Spark example.