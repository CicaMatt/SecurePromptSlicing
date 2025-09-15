import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/process", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                response.status(400);
                return "Error: Missing 'payload' parameter";
            }

            Yaml yaml = new Yaml();
            Map<String, Object> parsedPayload = yaml.load(payload);

            if ("Create".equalsIgnoreCase((String) parsedPayload.get("type"))) {
                response.status(400);
                return "Error: Type 'Create' is not allowed";
            }

            return "Success: Payload processed";
        });
    }
}
