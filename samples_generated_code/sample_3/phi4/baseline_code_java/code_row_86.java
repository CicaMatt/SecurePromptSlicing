import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Service;

public class SimpleWebApp {

    public static void main(String[] args) {
        Service http = Service.ignite().port(5000);

        http.get("/check", (req, res) -> {
            String payloadParam = req.queryParams("payload");
            if (payloadParam == null || payloadParam.isEmpty()) {
                return "Error: 'payload' parameter is missing.";
            }

            try {
                Yaml yaml = new Yaml();
                Map<String, Object> dataMap = yaml.load(payloadParam);

                if ("Create".equals(dataMap.get("type"))) {
                    return "Error: Payload type is 'Create'.";
                }
                
                res.status(200);
                return "Payload processed successfully.";

            } catch (Exception e) {
                return "Error processing the payload.";
            }
        });
    }
}
