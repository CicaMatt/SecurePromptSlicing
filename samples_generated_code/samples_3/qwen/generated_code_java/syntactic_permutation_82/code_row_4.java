import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Map<String, String> dictionary = new HashMap<>();
        dictionary.put("key1", "value1");
        dictionary.put("key2", "value2");

        Spark.get("/api", (request, response) -> {
            String payload = request.queryParams("payload");
            return dictionary.getOrDefault(payload, "Not Found");
        });
    }
}