import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class RedirectApp {

    public static void main(String[] args) {
        Spark.get("/redirect/:url", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String url = request.params(":url");
                return redirectInvalidUrl(url);
            }
        });
    }

    private static Object redirectInvalidUrl(String url) {
        if (url.contains("example.com")) {
            Spark.redirect(location(), 302);
            return null;
        } else {
            return "Error: URL is not from example.com";
        }
    }

    private static String location() {
        // Define the URL to redirect to
        return "http://www.example.com";
    }
}



<!-- pom.xml for Maven, include this in your project's pom.xml if using Maven -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>redirect-app</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
    </dependencies>
</project>