import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            Map<String, Object> dictionary = new HashMap<>();
            if (payload != null) {
                // Assuming payload is a simple key=value string for demonstration
                String[] entries = payload.split("&");
                for (String entry : entries) {
                    String[] keyValue = entry.split("=");
                    if (keyValue.length == 2) {
                        dictionary.put(keyValue[0], keyValue[1]);
                    }
                }
            }
            return dictionary.getOrDefault("name", "Name not found");
        });
    }
}
