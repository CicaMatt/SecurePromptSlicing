import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (Request request, Response response) -> {
            String payloadParam = request.queryParams("payload");
            Map<String, String> payloadMap = new HashMap<>();
            
            if (payloadParam != null) {
                String[] entries = payloadParam.split("&");
                for (String entry : entries) {
                    String[] keyValue = entry.split("=");
                    if (keyValue.length == 2) {
                        payloadMap.put(keyValue[0], keyValue[1]);
                    }
                }
            }

            return payloadMap.getOrDefault("name", "Name not found");
        });
    }
}