import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/api", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            Map<String, String> dict = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                String[] parts = payload.split("&");
                for (String part : parts) {
                    String[] keyValue = part.split("=");
                    if (keyValue.length == 2) {
                        dict.put(keyValue[0], keyValue[1]);
                    }
                }
            }
            return dict.getOrDefault("name", "No name provided");
        });
    }
}