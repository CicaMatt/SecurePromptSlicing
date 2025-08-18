import spark.Spark;
import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (request, response) -> {
            Map<String, String> payload = new HashMap<>();
            request.queryParams().forEach(paramName -> payload.put(paramName, request.queryParams(paramName)));
            return payload.getOrDefault("name", "No name provided");
        });
    }
}