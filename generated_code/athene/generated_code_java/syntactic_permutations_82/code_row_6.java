import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/api", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            Map<String, String> map = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                String[] pairs = payload.split("&");
                for (String pair : pairs) {
                    String[] keyValue = pair.split("=");
                    if (keyValue.length == 2) {
                        map.put(keyValue[0], keyValue[1]);
                    }
                }
            }
            return map.getOrDefault("name", "No name found");
        });
    }
}