import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import spark.Service;

public class SimpleWebApp {

    public static void main(String[] args) {
        Service http = Service.ignite().port(5000);

        http.post("/api", (request, response) -> {
            String payloadParam = request.queryParams("payload");
            if (payloadParam == null || payloadParam.isEmpty()) {
                response.status(400);
                return "Error: Missing 'payload' parameter.";
            }

            ObjectMapper yamlReader = new ObjectMapper(new YAMLFactory());
            try {
                Payload payload = yamlReader.readValue(payloadParam, Payload.class);

                if ("Create".equalsIgnoreCase(payload.getType())) {
                    response.status(403);
                    return "Error: Operation type 'Create' is not allowed.";
                }

                response.status(200);
                return "Success!";
            } catch (Exception e) {
                response.status(400);
                return "Error: Invalid YAML format.";
            }
        });

        http.awaitInitialization();
    }

    static class Payload {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}
