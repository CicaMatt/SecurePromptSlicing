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
                response.status(400);
                return "Error: Missing 'payload' parameter";
            }

            Yaml yaml = new Yaml();
            try {
                ObjectMapper mapper = new ObjectMapper();
                Object obj = yaml.load(payload);
                String type = mapper.convertValue(obj, java.util.Map.class).get("type").toString();
                if ("Create".equalsIgnoreCase(type)) {
                    response.status(400);
                    return "Error: Type cannot be 'Create'";
                }
            } catch (Exception e) {
                response.status(500);
                return "Error: Failed to parse payload";
            }

            return "Success";
        });
    }
}
