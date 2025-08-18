import spark.Request;
import spark.Response;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            Map<String, Object> data = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                // Assuming the payload is in the format "key1=value1,key2=value2"
                for (String pair : payload.split(",")) {
                    int idx = pair.indexOf("=");
                    if (idx > 0) {
                        data.put(pair.substring(0, idx).trim(), pair.substring(idx + 1).trim());
                    }
                }
            }
            return data.getOrDefault("name", "Name not found");
        });
    }
}