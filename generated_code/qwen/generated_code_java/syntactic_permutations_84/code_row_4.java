import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/", (request, response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                response.status(400);
                return "Error: Missing payload parameter";
            }

            Yaml yaml = new Yaml();
            ObjectMapper objectMapper = new ObjectMapper();
            try {
                Object obj = yaml.load(payload);
                String type = objectMapper.convertValue(obj, java.util.Map.class).get("type").toString();
                if ("Create".equalsIgnoreCase(type)) {
                    response.status(400);
                    return "Error: Type Create is not allowed";
                }
            } catch (Exception e) {
                response.status(400);
                return "Error: Invalid payload format";
            }

            return "Success";
        });
    }
}
