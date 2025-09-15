import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.io.IOException;
import java.util.Map;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(5000);
        Spark.get("/check", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                return "Error: No payload provided";
            }

            Yaml yaml = new Yaml();
            try {
                Map<String, Object> parsedPayload = yaml.load(payload);
                if ("error".equalsIgnoreCase((String) parsedPayload.get("type"))) {
                    return "Error: Payload type is error";
                }
            } catch (Exception e) {
                return "Error: Invalid YAML format";
            }

            return "Success: Payload processed";
        });
    }
}
