import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Spark.get("/api", (request, response) -> {
            String payload = request.queryParams("payload");
            Map<String, Object> map = new HashMap<>();
            // Assuming payload is a simple key=value string
            if (payload != null && !payload.isEmpty()) {
                String[] entries = payload.split("&");
                for (String entry : entries) {
                    String[] keyValue = entry.split("=");
                    if (keyValue.length == 2) {
                        map.put(keyValue[0], keyValue[1]);
                    }
                }
            }
            return map.getOrDefault("name", "Name not found");
        });
    }
}