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

        Spark.post("/process", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                return "Error: Payload parameter is missing.";
            }

            Yaml yaml = new Yaml();
            try {
                Map<String, Object> data = yaml.load(payload);
                String type = (String) data.get("type");
                if ("Create".equalsIgnoreCase(type)) {
                    return "Error: Type cannot be Create.";
                }
            } catch (Exception e) {
                return "Error: Failed to parse YAML payload.";
            }

            return "Payload processed successfully.";
        });
    }
}
