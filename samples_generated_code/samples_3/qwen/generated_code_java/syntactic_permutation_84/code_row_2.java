import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/", (request, response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                return "Error: No payload parameter found.";
            }

            try {
                Yaml yaml = new Yaml();
                Object obj = yaml.load(payload);
                if (obj instanceof java.util.Map) {
                    java.util.Map<?, ?> map = (java.util.Map<?, ?>) obj;
                    if ("Create".equals(map.get("type"))) {
                        return "Error: Type is Create.";
                    }
                }
            } catch (Exception e) {
                return "Error: Failed to parse payload.";
            }

            return "Payload processed successfully.";
        });
    }
}