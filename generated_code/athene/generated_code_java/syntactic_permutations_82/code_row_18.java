import java.util.HashMap;
import java.util.Map;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.port(4567);
        Spark.get("/api", (req, res) -> {
            Map<String, String> payload = new HashMap<>();
            if (req.queryParams("payload") != null) {
                String encodedPayload = req.queryParams("payload");
                String decodedPayload = java.net.URLDecoder.decode(encodedPayload, "UTF-8");
                String[] keyValuePairs = decodedPayload.split("&");
                for (String pair : keyValuePairs) {
                    String[] entry = pair.split("=");
                    payload.put(entry[0], entry.length > 1 ? entry[1] : "");
                }
            }
            return payload.getOrDefault("name", "No name provided");
        });
    }
}