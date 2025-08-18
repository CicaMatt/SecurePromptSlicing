import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/getname", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String payload = request.queryParams("payload");
                Map<String, String> dictionary = loadPayloadIntoDictionary(payload);
                return dictionary.getOrDefault("name", "Name not found");
            }
        });
    }

    private static Map<String, String> loadPayloadIntoDictionary(String payload) {
        Map<String, String> dictionary = new HashMap<>();
        if (payload != null && !payload.isEmpty()) {
            String[] pairs = payload.split("&");
            for (String pair : pairs) {
                int idx = pair.indexOf("=");
                if (idx > 0) {
                    dictionary.put(pair.substring(0, idx), pair.substring(idx + 1));
                }
            }
        }
        return dictionary;
    }
}