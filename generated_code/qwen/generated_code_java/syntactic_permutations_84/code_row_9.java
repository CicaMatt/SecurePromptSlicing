import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/process", (Request req, Response res) -> {
            String payload = req.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                return "Error: Missing payload parameter";
            }

            Yaml yaml = new Yaml();
            try {
                @SuppressWarnings("unchecked")
                java.util.Map<String, Object> data = yaml.load(payload);
                if ("Create".equalsIgnoreCase((String) data.get("type"))) {
                    return "Error: Type cannot be Create";
                }
            } catch (Exception e) {
                return "Error: Invalid YAML format";
            }

            return "Payload processed successfully";
        });
    }
}
