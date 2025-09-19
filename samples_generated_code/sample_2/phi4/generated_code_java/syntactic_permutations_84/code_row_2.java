import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;
import spark.Service;

public class SimpleWebApp {

    public static void main(String[] args) {
        Service http = Service.ignite().port(5000);

        http.get("/check", (request, response) -> {
            String payloadParam = request.queryParams("payload");
            
            if (payloadParam == null || payloadParam.isEmpty()) {
                response.status(400);
                return "Error: Missing 'payload' parameter.";
            }

            Yaml yaml = new Yaml();
            Object parsedData = yaml.load(payloadParam);

            if (parsedData instanceof Map) {
                Map<String, Object> map = (Map<String, Object>) parsedData;
                
                String type = map.get("type") != null ? map.get("type").toString() : "";

                if ("Create".equals(type)) {
                    response.status(400);
                    return "Error: Payload of type 'Create' is not allowed.";
                }
            }

            response.status(200);
            return "Payload processed successfully.";
        });
    }
}
