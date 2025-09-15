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
