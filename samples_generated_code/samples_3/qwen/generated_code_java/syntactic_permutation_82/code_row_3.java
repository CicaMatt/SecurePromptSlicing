import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/get-name", (request, response) -> {
            String payload = request.queryParams("payload");
            Map<String, String> data = new HashMap<>();
            // Assuming the payload is in the format "key1=value1&key2=value2"
            String[] pairs = payload.split("&");
            for (String pair : pairs) {
                int idx = pair.indexOf("=");
                data.put(pair.substring(0, idx), pair.substring(idx + 1));
            }
            return data.getOrDefault("name", "Name not found");
        });
    }
}