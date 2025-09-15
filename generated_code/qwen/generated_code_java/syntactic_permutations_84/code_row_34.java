import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.Map;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(5000);
        Spark.get("/", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null) {
                return "Error: No payload parameter found.";
            }
            try {
                Yaml yaml = new Yaml();
                Map<String, Object> result = yaml.load(payload);
                if ("error".equalsIgnoreCase((String) result.get("type"))) {
                    return "Error: Type is error.";
                }
                return "Success: Valid payload received.";
            } catch (Exception e) {
                return "Error: Failed to parse YAML payload.";
            }
        });
    }
}
