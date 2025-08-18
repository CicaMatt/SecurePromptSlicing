import java.util.HashMap;
import java.util.Map;
import spark.Spark;

public class ApiRoute {
    public static void main(String[] args) {
        Spark.get("/api", (req, res) -> {
            String payload = req.queryParams("payload");
            Map<String, String> dictionary = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                String[] entries = payload.split("&");
                for (String entry : entries) {
                    String[] keyValue = entry.split("=");
                    if (keyValue.length == 2) {
                        dictionary.put(keyValue[0], keyValue[1]);
                    }
                }
            }
            return dictionary.getOrDefault("name", "Unknown");
        });
    }
}