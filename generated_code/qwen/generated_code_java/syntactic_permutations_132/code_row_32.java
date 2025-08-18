import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldDecorator {

    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.params(":username");
                return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
            }
        });
    }
}



<!-- Place this content in a file named hello.html in the resources directory -->
<html>
<body>
<h1>Hello, ${username}!</h1>
</body>
</html>


To run this code, you need to have the Spark framework in your classpath. If you're using Maven, add the following dependency to your `pom.xml`:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>


If you're not using Maven, download the Spark library from [Spark's GitHub repository](https://github.com/perwendel/spark) and add it to your project. Note that this example does not use a template engine like Thymeleaf or FreeMarker; instead, it directly returns an HTML string. If you want to use `hello.html` as a template file, you would need to integrate a template engine with Spark.