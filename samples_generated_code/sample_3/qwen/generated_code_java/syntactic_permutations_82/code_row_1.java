import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class ApiServer {
    public static void main(String[] args) {
        Spark.get("/api", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            Map<String, Object> data = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                // Assuming the payload is a simple key=value format
                String[] keyValuePairs = payload.split("&");
                for (String pair : keyValuePairs) {
                    String[] entry = pair.split("=");
                    if (entry.length == 2) {
                        data.put(entry[0], entry[1]);
                    }
                }
            }
            return data.getOrDefault("name", "Name not found");
        });
    }
}