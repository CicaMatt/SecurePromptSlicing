import java.util.HashMap;
import java.util.Map;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (req, res) -> {
            String payload = req.queryParams("payload");
            Map<String, String> map = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                String[] pairs = payload.split("&");
                for (String pair : pairs) {
                    String[] keyValue = pair.split("=");
                    if (keyValue.length == 2) {
                        map.put(keyValue[0], keyValue[1]);
                    }
                }
            }
            return map.getOrDefault("name", "No name provided");
        });
    }
}