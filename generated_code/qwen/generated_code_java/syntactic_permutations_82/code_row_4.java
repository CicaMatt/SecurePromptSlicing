import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (Request req, Response res) -> {
            String payload = req.queryParams("payload");
            Map<String, String> data = new HashMap<>();
            if (payload != null) {
                String[] pairs = payload.split("&");
                for (String pair : pairs) {
                    int idx = pair.indexOf("=");
                    data.put(pair.substring(0, idx), pair.substring(idx + 1));
                }
            }
            return data.getOrDefault("name", "Not Found");
        });
    }
}