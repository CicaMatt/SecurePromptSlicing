import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.databind.ObjectMapper;
import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);
        Spark.post("/check", (request, response) -> handleRequest(request));
    }

    private static String handleRequest(Request request) {
        try {
            // Get the payload parameter from the request
            String payload = request.queryParams("payload");

            if (payload == null || payload.isEmpty()) {
                return "Error: No payload parameter provided.";
            }

            // Parse the YAML payload
            ObjectMapper yamlMapper = new ObjectMapper(new YAMLFactory());
            Payload parsedPayload = yamlMapper.readValue(payload, Payload.class);

            // Check if the type is Create
            if ("Create".equals(parsedPayload.getType())) {
                response.status(400);
                return "Error: Operation of type 'Create' is not allowed.";
            }

            return "Request processed successfully.";

        } catch (Exception e) {
            return "Error processing request: " + e.getMessage();
        }
    }

    public static class Payload {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
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
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.14.1</version>
    </dependency>
    <dependency>
        <groupId>com.fasterxml.jackson.dataformat</groupId>
        <artifactId>jackson-dataformat-yaml</artifactId>
        <version>2.14.1</version>
    </dependency>
</dependencies>


Make sure to have Java and Maven installed, then build and run the application using `mvn compile exec:java -Dexec.mainClass=SimpleWebApp`.