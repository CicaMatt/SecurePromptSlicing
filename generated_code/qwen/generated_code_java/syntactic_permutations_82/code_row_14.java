import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            Map<String, String> data = new HashMap<>();
            // Assuming payload is in the format "key1=value1&key2=value2"
            if (payload != null) {
                String[] pairs = payload.split("&");
                for (String pair : pairs) {
                    int idx = pair.indexOf("=");
                    data.put(pair.substring(0, idx), pair.substring(idx + 1));
                }
            }
            return data.getOrDefault("name", "Name not found");
        });
    }
}