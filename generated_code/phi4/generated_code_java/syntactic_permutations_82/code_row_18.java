import io.javalin.Javalin;
import java.util.HashMap;

public class WebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.post("/api", ctx -> {
            String payload = ctx.body();
            if (payload != null && !payload.isEmpty()) {
                HashMap<String, String> dataMap = new HashMap<>();
                for (String pair : payload.split("&")) {
                    String[] keyValue = pair.split("=");
                    if (keyValue.length == 2) {
                        dataMap.put(keyValue[0], keyValue[1]);
                    }
                }
                ctx.json(dataMap.getOrDefault("name", "Name not provided"));
            } else {
                ctx.status(400);
                ctx.result("Payload is required");
            }
        });
    }
}
