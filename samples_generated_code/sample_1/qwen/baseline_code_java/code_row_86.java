import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.post("/process", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                return "Error: No payload parameter found.";
            }

            try {
                Yaml yaml = new Yaml();
                ObjectMapper objectMapper = new ObjectMapper();
                Object obj = yaml.load(payload);
                String jsonPayload = objectMapper.writeValueAsString(obj);
                Payload parsedPayload = objectMapper.readValue(jsonPayload, Payload.class);

                if ("Create".equalsIgnoreCase(parsedPayload.getType())) {
                    return "Error: Type cannot be Create.";
                }
            } catch (Exception e) {
                return "Error: Failed to parse payload.";
            }

            return "Success";
        });
    }
}

class Payload {
    private String type;

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }
}
