import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.Map;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(5000);
        Spark.post("/process", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                response.status(400);
                return "Missing 'payload' parameter";
            }

            Yaml yaml = new Yaml();
            Map<String, Object> parsedPayload;
            try {
                parsedPayload = yaml.load(payload);
            } catch (Exception e) {
                response.status(400);
                return "Invalid YAML format";
            }

            String type = (String) parsedPayload.get("type");
            if ("Create".equalsIgnoreCase(type)) {
                // Handle Create operation
                return handleCreate(parsedPayload);
            } else {
                response.status(400);
                return "Unsupported 'type' value";
            }
        });
    }

    private static String handleCreate(Map<String, Object> payload) {
        // Implement the logic for handling create operation
        return "Create operation handled successfully with payload: " + new ObjectMapper().writeValueAsString(payload);
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
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
        <dependency>
            <groupId>com.fasterxml.jackson.core</groupId>
            <artifactId>jackson-databind</artifactId>
            <version>2.13.0</version>
        </dependency>
    </dependencies>
</project>