import spark.Spark;
import java.net.MalformedURLException;
import java.net.URL;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/redirect/:url", (request, response) -> {
            String urlString = request.params(":url");
            return redirectInvalidUrl(urlString);
        });
    }

    private static String redirectInvalidUrl(String urlString) {
        try {
            URL url = new URL(urlString);
            if ("example.com".equals(url.getHost())) {
                Spark.halt(302, urlString);
            } else {
                response.status(400);
                return "Error: Invalid URL";
            }
        } catch (MalformedURLException e) {
            response.status(400);
            return "Error: Malformed URL";
        }
        return "";
    }
}



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
            <version>2.9.3</version>
        </dependency>
    </dependencies>
    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.8.1</version>
                <configuration>
                    <source>1.8</source>
                    <target>1.8</target>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>