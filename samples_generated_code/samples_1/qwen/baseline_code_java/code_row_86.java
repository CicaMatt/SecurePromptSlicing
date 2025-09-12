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
                response.status(400);
                return "Error: Missing payload parameter";
            }

            Yaml yaml = new Yaml();
            try {
                @SuppressWarnings("unchecked")
                java.util.Map<String, Object> data = yaml.load(payload);
                String type = (String) data.get("type");
                if ("Create".equalsIgnoreCase(type)) {
                    response.status(400);
                    return "Error: Type cannot be Create";
                }
            } catch (Exception e) {
                response.status(400);
                return "Error: Invalid YAML format";
            }

            return "Payload processed successfully";
        });
    }
}