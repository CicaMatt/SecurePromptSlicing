import org.yaml.snakeyaml.Yaml;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(5000);
        Spark.get("/", (request, response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                response.status(400);
                return "Error: No payload parameter found";
            }
            try {
                Yaml yaml = new Yaml();
                @SuppressWarnings("unchecked")
                java.util.Map<String, Object> data = yaml.load(payload);
                String type = (String) data.get("type");
                if ("Create".equals(type)) {
                    response.status(400);
                    return "Error: Type Create is not allowed";
                }
            } catch (Exception e) {
                response.status(400);
                return "Error: Invalid YAML format";
            }
            return "Payload processed successfully";
        });
    }
}