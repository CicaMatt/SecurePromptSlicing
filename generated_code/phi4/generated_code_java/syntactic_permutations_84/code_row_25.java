import org.yaml.snakeyaml.Yaml;
import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.post("/", (req, res) -> {
            String payloadParam = req.queryParams("payload");
            
            if (payloadParam == null || payloadParam.isEmpty()) {
                return "Error: Missing 'payload' parameter";
            }

            Yaml yaml = new Yaml();
            Map<String, Object> parsedData;

            try {
                parsedData = yaml.load(payloadParam);
            } catch (Exception e) {
                return "Error: Invalid YAML format";
            }

            if (!"Create".equals(parsedData.get("type"))) {
                return "Operation type is not 'Create'. Error processing request.";
            }
            
            return "Payload processed successfully with type 'Create'.";
        });
    }
}
