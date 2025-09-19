import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApplication {
    public static void main(String[] args) {
        Spark.get("/redirect/:url", (Request req, Response res) -> {
            String url = req.params(":url");
            return redirectInvalidUrl(url);
        });
    }

    private static String redirectInvalidUrl(String url) {
        if (url.contains("example.com")) {
            Spark.halt(301, "Redirecting...", "Location", url);
        } else {
            Spark.halt(400, "Invalid URL");
        }
        return "";
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/maven-v4_0_0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>webapp</artifactId>
    <packaging>jar</packaging>
    <version>1.0-SNAPSHOT</version>
    <name>WebApplication</name>
    <url>http://maven.apache.org</url>

    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.codehaus.mojo</groupId>
                <artifactId>exec-maven-plugin</artifactId>
                <version>1.6.0</version>
                <configuration>
                    <mainClass>WebApplication</mainClass>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>