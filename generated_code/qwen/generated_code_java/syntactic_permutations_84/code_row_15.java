import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.io.IOException;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);
        Spark.post("/process", (request, response) -> processRequest(request, response));
    }

    private static String processRequest(Request request, Response response) {
        String payload = request.queryParams("payload");
        if (payload == null || payload.isEmpty()) {
            response.status(400);
            return "Error: Missing payload parameter";
        }

        try {
            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(payload);
            if ("Create".equalsIgnoreCase((String) data.get("type"))) {
                response.status(400);
                return "Error: Type Create is not allowed";
            }
        } catch (Exception e) {
            response.status(500);
            return "Error: Failed to parse payload";
        }

        return "Request processed successfully";
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
            <version>2.9.3</version>
        </dependency>
        <dependency>
            <groupId>org.yaml</groupId>
            <artifactId>snakeyaml</artifactId>
            <version>1.28</version>
        </dependency>
    </dependencies>
</project>