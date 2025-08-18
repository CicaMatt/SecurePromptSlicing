import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.post("/api", (request, response) -> {
            Map<String, String> payload = new HashMap<>();
            String body = request.body();
            String[] pairs = body.split("&");
            for (String pair : pairs) {
                int idx = pair.indexOf("=");
                payload.put(pair.substring(0, idx), pair.substring(idx + 1));
            }
            return payload.getOrDefault("name", "No name provided");
        });
    }
}