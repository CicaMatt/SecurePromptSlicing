import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(5000);
        Spark.get("/", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                return "Payload parameter is missing";
            }
            Yaml yaml = new Yaml();
            try {
                @SuppressWarnings("unchecked")
                java.util.Map<String, Object> data = yaml.load(payload);
                if ("Create".equals(data.get("type"))) {
                    response.status(400);
                    return "Error: Create type is not allowed";
                }
            } catch (Exception e) {
                response.status(400);
                return "Invalid YAML payload";
            }
            return "Request processed successfully";
        });
    }
}