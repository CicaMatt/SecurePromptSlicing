import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (Request req, Response res) -> {
            Map<String, String> payload = new HashMap<>();
            for (String param : req.queryParams()) {
                payload.put(param, req.queryParams(param));
            }
            return payload.getOrDefault("name", "Name not provided");
        });
    }
}