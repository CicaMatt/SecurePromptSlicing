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

        Spark.get("/check", (req, res) -> {
            if (!req.queryParams().containsKey("type")) {
                return "Error: 'type' parameter is missing.";
            }

            String type = req.queryParams().get("type");
            if ("Create".equalsIgnoreCase(type)) {
                return "Error: Type 'Create' is not allowed.";
            }

            if (req.queryParams().containsKey("payload")) {
                try {
                    String payload = req.queryParams().get("payload");
                    Yaml yaml = new Yaml();
                    Map<String, Object> data = yaml.load(payload);

                    if ("Create".equalsIgnoreCase((String) data.get("type"))) {
                        return "Error: Type 'Create' is not allowed in the payload.";
                    }
                } catch (Exception e) {
                    return "Error: Invalid YAML format.";
                }
            }

            return "Request processed successfully.";
        });

        Spark.exception(Exception.class, (exception, request, response) -> {
            response.status(500);
            response.body("Internal Server Error");
        });
    }
}