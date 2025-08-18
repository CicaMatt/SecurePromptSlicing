import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (request, response) -> {
            String payload = request.queryParams("payload");
            Map<String, String> dictionary = new HashMap<>();
            if (payload != null) {
                dictionary.put("payload", payload);
            }
            return dictionary;
        }, new spark.json.JsonTransformer());
    }
}



<!-- pom.xml for Maven -->
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>webapp</artifactId>
    <version>1.0-SNAPSHOT</version>

    <dependencies>
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
        <dependency>
            <groupId>com.google.code.gson</groupId>
            <artifactId>gson</artifactId>
            <version>2.8.8</version>
        </dependency>
    </dependencies>
</project>