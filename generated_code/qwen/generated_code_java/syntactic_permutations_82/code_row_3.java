import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            Map<String, String> dictionary = new HashMap<>();
            if (payload != null) {
                String[] pairs = payload.split("&");
                for (String pair : pairs) {
                    int idx = pair.indexOf("=");
                    dictionary.put(pair.substring(0, idx), pair.substring(idx + 1));
                }
            }
            return dictionary.getOrDefault("name", "Not Found");
        });
    }
}