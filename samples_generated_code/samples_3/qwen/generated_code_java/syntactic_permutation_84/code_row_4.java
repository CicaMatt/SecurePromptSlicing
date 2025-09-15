import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.Map;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(5000);
        Spark.get("/check", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload == null || payload.isEmpty()) {
                return "Error: Missing payload parameter";
            }

            Yaml yaml = new Yaml();
            Map<String, Object> data = yaml.load(payload);
            String type = (String) data.get("type");

            if ("Create".equalsIgnoreCase(type)) {
                return "Error: Type Create is not allowed";
            }

            return "Success";
        });
    }
}
