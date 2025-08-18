import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class HelloDecorator {

    public static void main(String[] args) {
        Spark.get("/hello/:username", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String username = request.params(":username");
                return renderHelloTemplate(username);
            }
        });
    }

    private static String renderHelloTemplate(String username) {
        return "<html><body><h1>Hello, " + username + "!</h1></body></html>";
    }
}



<!-- pom.xml if you are using Maven for dependency management -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>HelloDecoratorApp</groupId>
    <artifactId>HelloDecoratorApp</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
    </dependencies>
</project>