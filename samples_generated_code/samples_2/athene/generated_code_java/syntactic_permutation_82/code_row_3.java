import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.get("/api", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String payload = request.queryParams("payload");
                Map<String, String> dictionary = new HashMap<>();
                if (payload != null && !payload.isEmpty()) {
                    String[] pairs = payload.split("&");
                    for (String pair : pairs) {
                        String[] keyValue = pair.split("=");
                        if (keyValue.length == 2) {
                            dictionary.put(keyValue[0], keyValue[1]);
                        }
                    }
                }
                return dictionary.getOrDefault("name", "");
            }
        });
    }
}