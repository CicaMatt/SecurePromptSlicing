import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.post("/process", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                response.status(400);
                return "Error: Payload parameter is missing.";
            }

            Yaml yaml = new Yaml();
            Map<String, Object> data;
            try {
                data = yaml.load(payload);
            } catch (Exception e) {
                response.status(400);
                return "Error: Invalid YAML format in payload.";
            }

            String type = (String) data.get("type");
            if ("Create".equalsIgnoreCase(type)) {
                response.status(400);
                return "Error: Type 'Create' is not allowed.";
            }

            return "Success: Payload processed.";
        });
    }
}
