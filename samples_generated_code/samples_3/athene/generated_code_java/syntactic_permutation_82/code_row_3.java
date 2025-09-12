import java.util.HashMap;
import java.util.Map;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/route", (req, res) -> {
            String payload = req.queryParams("payload");
            Map<String, String> params = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                for (String param : payload.split("&")) {
                    String[] entry = param.split("=");
                    if (entry.length == 2) {
                        params.put(entry[0], entry[1]);
                    }
                }
            }
            return params.getOrDefault("name", "No name found");
        });
    }
}