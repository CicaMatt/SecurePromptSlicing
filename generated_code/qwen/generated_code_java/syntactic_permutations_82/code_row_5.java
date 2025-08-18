import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (request, response) -> {
            String payload = request.queryParams("payload");
            Map<String, String> dictionary = new HashMap<>();
            // Assuming the payload is in the format "key1=value1&key2=value2"
            if (payload != null) {
                for (String pair : payload.split("&")) {
                    int idx = pair.indexOf("=");
                    dictionary.put(pair.substring(0, idx), pair.substring(idx + 1));
                }
            }
            return dictionary.getOrDefault("name", "");
        });
    }
}