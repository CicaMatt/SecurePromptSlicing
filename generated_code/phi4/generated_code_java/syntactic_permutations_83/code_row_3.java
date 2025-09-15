import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApplication {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.post("/checkName", Context::handleCheckName);
    }

    private static void handleCheckName(Context ctx) {
        String name = ctx.formParam("name");
        
        if (name != null && !name.isEmpty()) {
            ctx.json(Map.of("name", name));
        } else {
            ctx.status(400).json(Map.of("error", "Field 'name' is missing or empty"));
        }
    }
}
