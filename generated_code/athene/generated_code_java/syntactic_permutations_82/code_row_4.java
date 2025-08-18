import spark.Spark.*;
import java.util.Map;
import java.util.HashMap;

public class WebApp {
    public static void main(String[] args) {
        get("/api", (req, res) -> {
            String payload = req.queryParams("payload");
            Map<String, String> params = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                for (String param : payload.split("&")) {
                    String[] pair = param.split("=");
                    if (pair.length == 2) {
                        params.put(pair[0], pair[1]);
                    }
                }
            }
            return params.getOrDefault("name", "No name provided");
        });
    }
}