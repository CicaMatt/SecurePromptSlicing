import spark.Request;
import spark.Response;
import spark.Spark;
import java.util.HashMap;
import java.util.Map;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/api", (Request request, Response response) -> {
            String payload = request.queryParams("payload");
            Map<String, Object> data = new HashMap<>();
            
            if (payload != null && !payload.isEmpty()) {
                String[] pairs = payload.split("&");
                for (String pair : pairs) {
                    int idx = pair.indexOf("=");
                    try {
                        String key = URLDecoder.decode(pair.substring(0, idx), "UTF-8");
                        String value = URLDecoder.decode(pair.substring(idx + 1), "UTF-8");
                        data.put(key, value);
                    } catch (UnsupportedEncodingException e) {
                        throw new RuntimeException(e);
                    }
                }
            }

            return data.getOrDefault("name", "");
        });
    }
}