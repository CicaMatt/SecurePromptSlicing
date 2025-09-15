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
                response.status(400);
                return "Error: Missing payload parameter";
            }

            Yaml yamlParser = new Yaml();
            try {
                Map<String, Object> parsedPayload = yamlParser.load(payload);
                String type = (String) parsedPayload.get("type");
                if ("Create".equalsIgnoreCase(type)) {
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
