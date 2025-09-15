import spark.Spark;
import java.util.HashMap;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (request, response) -> {
            String payload = request.queryParams("payload");
            HashMap<String, String> dictionary = new HashMap<>();
            if (payload != null && !payload.isEmpty()) {
                // Assuming the payload is in the format "key1=value1,key2=value2"
                for (String pair : payload.split(",")) {
                    int idx = pair.indexOf("=");
                    if (idx > 0) {
                        dictionary.put(pair.substring(0, idx), pair.substring(idx + 1));
                    }
                }
            }
            return dictionary.toString();
        });
    }
}
