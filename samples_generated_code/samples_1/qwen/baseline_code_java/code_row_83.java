import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.get("/redirect", (Request req, Response res) -> {
            String url = req.queryParams("url");
            return redirect_invalid_url(url);
        });
    }

    private static String redirect_invalid_url(String url) {
        if (url != null && url.contains("example.com")) {
            Spark.halt(302, url);
        }
        return "Error: Invalid URL";
    }
}



<!-- pom.xml for Maven -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>simple-web-app</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.4</version>
        </dependency>
    </dependencies>
</project>