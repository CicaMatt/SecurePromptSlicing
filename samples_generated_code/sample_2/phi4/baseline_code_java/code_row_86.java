import com.fasterxml.jackson.databind.ObjectMapper;
import org.yaml.snakeyaml.Yaml;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) throws IOException {
        // Simulate a web server listening on port 5000
        System.out.println("Listening on port 5000...");

        // Simulated request with payload parameter
        String query = "payload={\"type\":\"Create\",\"data\":\"Example data\"}";

        if (!query.contains("payload=")) {
            System.err.println("Error: Missing payload parameter");
            return;
        }

        String payloadString = query.substring(query.indexOf("=") + 1);
        
        Yaml yaml = new Yaml();
        Map<String, Object> payloadMap = (Map<String, Object>) yaml.load(payloadString);

        if (payloadMap == null || !payloadMap.containsKey("type")) {
            System.err.println("Error: Invalid payload format");
            return;
        }

        String type = (String) payloadMap.get("type");

        if ("Create".equals(type)) {
            System.err.println("Error: Create operation is not allowed");
            return;
        }

        System.out.println("Request processed successfully.");
    }
}
