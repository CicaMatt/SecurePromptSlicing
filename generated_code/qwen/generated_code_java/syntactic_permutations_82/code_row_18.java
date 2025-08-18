import spark.Spark;
import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (request, response) -> {
            String payload = request.queryParams("payload");
            Map<String, String> dictionary = new HashMap<>();
            
            // Assuming the payload is a simple key=value pair
            if (payload != null && payload.contains("=")) {
                String[] parts = payload.split("=");
                if (parts.length == 2) {
                    dictionary.put(parts[0], parts[1]);
                }
            }

            return dictionary.getOrDefault("name", "Name not found");
        });
    }
}