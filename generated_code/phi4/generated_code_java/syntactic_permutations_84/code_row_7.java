import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.io.IOException;
import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/", (req, res) -> "Welcome to the web application!");

        Spark.post("/process", (req, res) -> processPayload(req, res));
    }

    private static String processPayload(Request req, Response res) throws IOException {
        if (!req.queryParams().containsKey("payload")) {
            return "Error: payload parameter is missing.";
        }

        String yamlString = req.queryParams("payload");
        Yaml yaml = new Yaml();
        Map<String, Object> dataMap = yaml.load(yamlString);

        if (dataMap == null || !dataMap.containsKey("type") || !"Create".equals(dataMap.get("type"))) {
            return "Error: Payload type is not 'Create'.";
        }

        // If the type is Create, return an error message
        return "Error: Operation of type 'Create' is not allowed.";
    }
}


To run this code, you need to include the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
    <dependency>
        <groupId>org.yaml</groupId>
        <artifactId>snakeyaml</artifactId>
        <version>1.33</version>
    </dependency>
</dependencies>


Ensure you have the necessary libraries in your classpath to compile and run this application.