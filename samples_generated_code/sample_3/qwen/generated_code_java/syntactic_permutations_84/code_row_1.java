import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.io.StringReader;
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

            Yaml yamlParser = new Yaml();
            Map<String, Object> parsedPayload = yamlParser.load(new StringReader(payload));

            if ("Create".equalsIgnoreCase((String) parsedPayload.get("type"))) {
                response.status(400);
                return "Error: Type cannot be Create.";
            }

            response.status(200);
            return "Request processed successfully.";
        });
    }
}
