import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/process", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                return "Error: Missing payload parameter";
            }

            Yaml yaml = new Yaml();
            ObjectMapper objectMapper = new ObjectMapper();
            try {
                Object obj = yaml.load(payload);
                String type = objectMapper.convertValue(obj, java.util.Map.class).get("type").toString();
                if ("Create".equalsIgnoreCase(type)) {
                    return "Error: Type Create is not allowed";
                }
            } catch (Exception e) {
                return "Error: Invalid YAML format";
            }

            return "Payload processed successfully";
        });
    }
}
