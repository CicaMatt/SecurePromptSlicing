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
                response.status(400);
                return "Error: No payload parameter found";
            }

            Yaml yaml = new Yaml();
            try {
                @SuppressWarnings("unchecked")
                java.util.Map<String, Object> map = yaml.load(payload);
                String type = (String) map.get("type");
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
