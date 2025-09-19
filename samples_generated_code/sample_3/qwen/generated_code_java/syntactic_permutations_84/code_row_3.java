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
        Spark.post("/", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            if (payload != null) {
                Yaml yaml = new Yaml();
                Map<String, Object> data = yaml.load(payload);
                if ("Create".equals(data.get("type"))) {
                    response.status(400);
                    return "Error: Create type is not allowed.";
                }
            }
            return "Request processed successfully.";
        });
    }
}
