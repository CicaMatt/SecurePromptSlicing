import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Map<String, String> data = new HashMap<>();
        data.put("key1", "value1");
        data.put("key2", "value2");

        Spark.get("/api", (request, response) -> {
            String payload = request.queryParams("payload");
            return data.getOrDefault(payload, "Not Found");
        });
    }
}
