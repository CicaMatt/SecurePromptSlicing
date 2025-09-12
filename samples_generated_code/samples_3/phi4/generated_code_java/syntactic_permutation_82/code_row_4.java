import io.javalin.Javalin;
import java.util.HashMap;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/api", ctx -> {
            String payload = ctx.queryParam("payload");
            
            if (payload != null) {
                try {
                    HashMap<String, Object> dictionary = parsePayload(payload);
                    if (dictionary.containsKey("name")) {
                        ctx.result("{\"name\": \"" + dictionary.get("name") + "\"}");
                    } else {
                        ctx.status(400).result("{\"error\": \"Name not found in payload\"}");
                    }
                } catch (Exception e) {
                    ctx.status(400).result("{\"error\": \"Invalid payload format\"}");
                }
            } else {
                ctx.status(400).result("{\"error\": \"Payload parameter is required\"}");
            }
        });
    }

    private static HashMap<String, Object> parsePayload(String payload) throws Exception {
        // Simple JSON parser logic for demonstration purposes
        if (payload == null || !payload.startsWith("{") || !payload.endsWith("}")) {
            throw new Exception("Invalid JSON format");
        }

        HashMap<String, Object> dictionary = new HashMap<>();
        payload = payload.substring(1, payload.length() - 1); // Remove braces

        String[] pairs = payload.split(",");
        for (String pair : pairs) {
            String[] keyValue = pair.split(":");
            if (keyValue.length != 2) continue;

            String key = keyValue[0].trim().replaceAll("\"", "");
            String value = keyValue[1].trim().replaceAll("\"", "");

            dictionary.put(key, value);
        }

        return dictionary;
    }
}