import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/api", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            Map<String, String> data = loadData(payload);
            return data.getOrDefault("name", "Name not found");
        });
    }

    private static Map<String, String> loadData(String payload) {
        // Simulate loading data based on the payload
        Map<String, String> data = new HashMap<>();
        if ("testPayload".equals(payload)) {
            data.put("name", "John Doe");
        }
        return data;
    }
}