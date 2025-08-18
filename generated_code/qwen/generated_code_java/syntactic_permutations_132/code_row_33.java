import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloWorldServer {

    public static void main(String[] args) {
        Spark.get("/hello/:username", (request, response) -> {
            String username = request.params(":username");
            return renderHelloTemplate(username);
        });
    }

    private static String renderHelloTemplate(String username) {
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }
}



<!-- This is the contents of hello.html which would be used in a more complex setup -->
<html>
<body>
<h1>Hello, ${username}!</h1>
</body>
</html>


Note: The provided Java code uses the Spark framework for simplicity. To run this code, you need to add the Spark dependency to your project. For Maven, add the following to your `pom.xml`:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>


For Gradle, add this to your `build.gradle`:


dependencies {
    implementation 'com.sparkjava:spark-core:2.9.3'
}


The provided Java code directly renders the HTML content in the `renderHelloTemplate` method for simplicity. In a more complex application, you would use a template engine like Thymeleaf or Freemarker to render the `hello.html` file with the username variable.