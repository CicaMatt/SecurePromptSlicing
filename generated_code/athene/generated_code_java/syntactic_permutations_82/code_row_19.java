import java.util.HashMap;
import java.util.Map;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (req, res) -> {
            String payload = req.queryParams("payload");
            Map<String, String> params = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                String[] entries = payload.split("&");
                for (String entry : entries) {
                    String[] keyValue = entry.split("=");
                    if (keyValue.length == 2) {
                        params.put(keyValue[0], keyValue[1]);
                    }
                }
            }
            return params.getOrDefault("name", "No name provided");
        });
    }
}