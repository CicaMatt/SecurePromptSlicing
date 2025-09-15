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
