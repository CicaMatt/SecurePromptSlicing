import java.util.HashMap;
import java.util.Map;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/api", (req, res) -> {
            String payload = req.queryParams("payload");
            Map<String, String> dictionary = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                String[] params = payload.split("&");
                for (String param : params) {
                    String[] keyValue = param.split("=");
                    if (keyValue.length == 2) {
                        dictionary.put(keyValue[0], keyValue[1]);
                    }
                }
            }
            return dictionary.getOrDefault("name", "No name provided");
        });
    }
}