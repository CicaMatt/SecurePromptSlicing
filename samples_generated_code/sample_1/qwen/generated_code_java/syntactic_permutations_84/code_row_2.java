import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/check", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                response.status(400);
                return "Error: Missing payload parameter";
            }

            Yaml yaml = new Yaml();
            try {
                ObjectMapper objectMapper = new ObjectMapper();
                Object obj = yaml.load(payload);
                String type = objectMapper.convertValue(obj, java.util.Map.class).get("type").toString();
                if ("Create".equals(type)) {
                    response.status(400);
                    return "Error: Type Create is not allowed";
                }
            } catch (Exception e) {
                response.status(400);
                return "Error: Invalid YAML payload";
            }

            return "Success";
        });
    }
}
