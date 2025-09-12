import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (Request req, Response res) -> {
            String payload = req.queryParams("payload");
            Map<String, String> data = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                String[] pairs = payload.split("&");
                for (String pair : pairs) {
                    int idx = pair.indexOf("=");
                    if (idx > 0) {
                        data.put(pair.substring(0, idx), pair.substring(idx + 1));
                    }
                }
            }
            return data.getOrDefault("name", "Name not found");
        });
    }
}