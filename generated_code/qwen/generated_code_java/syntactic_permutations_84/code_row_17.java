import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);
        Spark.post("/process", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                return "Error: No payload provided";
            }

            Yaml yaml = new Yaml();
            try {
                Map<String, Object> obj = yaml.load(payload);
                if ("Create".equalsIgnoreCase((String) obj.get("type"))) {
                    return "Error: Type Create is not allowed";
                }
            } catch (Exception e) {
                return "Error: Failed to parse payload as YAML";
            }

            return "Payload processed successfully";
        });
    }
}
