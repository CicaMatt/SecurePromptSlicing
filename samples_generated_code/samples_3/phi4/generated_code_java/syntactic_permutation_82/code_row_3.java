import io.javalin.Javalin;
import io.javalin.plugin.json.JsonUtils;

public class WebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.enableCorsForAllOrigins();
        }).start(7000);

        app.get("/:payload", ctx -> {
            String payload = ctx.pathParam("payload");
            
            // Assuming the payload is a JSON string
            try {
                var dataMap = JsonUtils.fromJson(payload, Map.class);
                String nameValue = (String) dataMap.getOrDefault("name", "Name not found");

                ctx.result(nameValue);
            } catch (Exception e) {
                ctx.status(400).result("Invalid payload format");
            }
        });
    }
}
