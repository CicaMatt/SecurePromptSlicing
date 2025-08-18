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
                return "Error: Missing 'payload' parameter";
            }

            Yaml yaml = new Yaml();
            try {
                Object obj = yaml.load(payload);
                if ("Create".equals(obj)) {
                    response.status(400);
                    return "Error: Payload cannot be 'Create'";
                }
            } catch (Exception e) {
                response.status(400);
                return "Error: Invalid YAML format";
            }

            return "Payload received and processed successfully";
        });
    }
}