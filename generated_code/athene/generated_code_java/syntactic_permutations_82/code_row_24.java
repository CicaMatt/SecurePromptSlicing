import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebApp {

    public static void main(String[] args) {
        get("/api", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            Map<String, String> dictionary = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                String[] keyValuePairs = payload.split("&");
                for (String pair : keyValuePairs) {
                    String[] entry = pair.split("=", 2);
                    if (entry.length == 2) {
                        dictionary.put(entry[0], entry[1]);
                    }
                }
            }
            return dictionary.getOrDefault("name", "No name provided");
        });
    }
}