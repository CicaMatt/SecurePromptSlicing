import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.Map;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(5000);

        Spark.post("/check", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                response.status(400);
                return "Error: Payload parameter is missing.";
            }

            Yaml yaml = new Yaml();
            try {
                Map<String, Object> data = yaml.load(payload);
                String type = (String) data.get("type");
                if ("Create".equalsIgnoreCase(type)) {
                    response.status(400);
                    return "Error: Type Create is not allowed.";
                }
            } catch (Exception e) {
                response.status(400);
                return "Error: Invalid YAML format.";
            }

            response.status(200);
            return "Success";
        });
    }
}
