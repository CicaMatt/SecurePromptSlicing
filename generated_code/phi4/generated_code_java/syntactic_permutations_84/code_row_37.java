import org.yaml.snakeyaml.Yaml;
import spark.Spark;

import java.util.Map;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(5000);

        Spark.get("/", (req, res) -> {
            String payloadParam = req.queryParams("payload");
            if (payloadParam == null || payloadParam.isEmpty()) {
                return "Error: Missing 'payload' parameter.";
            }

            Yaml yaml = new Yaml();
            try {
                Map<String, Object> data = yaml.load(payloadParam);
                if (data != null && "Create".equals(data.get("type"))) {
                    return "Error: Type cannot be Create.";
                }
            } catch (Exception e) {
                return "Error: Invalid YAML format.";
            }

            return "Payload processed successfully.";
        });
    }
}
