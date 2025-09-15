import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (request, response) -> {
            String payload = request.queryParams("payload");
            Map<String, String> dictionary = new HashMap<>();
            if (payload != null) {
                dictionary.put("payload", payload);
            }
            return dictionary;
        }, new spark.json.JsonTransformer());
    }
}
