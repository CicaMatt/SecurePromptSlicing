import java.util.Map;
import java.util.HashMap;
import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/api", (req, res) -> {
            String payload = req.queryParams("payload");
            Map<String, String> data = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                String[] parts = payload.split(",");
                for (String part : parts) {
                    String[] keyValue = part.split(":");
                    if (keyValue.length == 2) {
                        data.put(keyValue[0], keyValue[1]);
                    }
                }
            }
            return data.getOrDefault("name", "No name found");
        });
    }
}