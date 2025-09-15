import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);
        Spark.get("/", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                response.status(400);
                return "Error: Missing 'payload' parameter";
            }
            
            ObjectMapper yamlReader = new ObjectMapper(new YAMLFactory());
            try {
                Object obj = yamlReader.readValue(payload, Object.class);
                if (!(obj instanceof String)) {
                    response.status(400);
                    return "Error: Payload is not a valid string";
                }
                return "Payload processed successfully";
            } catch (Exception e) {
                response.status(400);
                return "Error: Invalid YAML format";
            }
        });
    }
}
