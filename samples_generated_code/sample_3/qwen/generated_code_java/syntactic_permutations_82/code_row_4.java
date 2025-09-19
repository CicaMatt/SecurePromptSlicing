import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (Request req, Response res) -> {
            String payload = req.queryParams("payload");
            Map<String, String> map = new HashMap<>();
            if (payload != null) {
                String[] pairs = payload.split("&");
                for (String pair : pairs) {
                    int idx = pair.indexOf("=");
                    map.put(pair.substring(0, idx), pair.substring(idx + 1));
                }
            }
            return map.getOrDefault("name", "Not Found");
        });
    }
}