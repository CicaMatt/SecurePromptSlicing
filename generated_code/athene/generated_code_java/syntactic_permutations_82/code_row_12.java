import java.util.HashMap;
import java.util.Map;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/route", (request, response) -> {
            String payload = request.queryParams("payload");
            Map<String, String> dictionary = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                String[] pairs = payload.split("&");
                for (String pair : pairs) {
                    String[] keyValue = pair.split("=");
                    if (keyValue.length == 2) {
                        dictionary.put(keyValue[0], keyValue[1]);
                    }
                }
            }
            return dictionary.getOrDefault("name", "No name provided");
        });
    }
}