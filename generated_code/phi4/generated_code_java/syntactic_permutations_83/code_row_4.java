import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebApplication {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.post("/check-name", ctx -> {
            String name = ctx.formParam("name");
            if (name != null && !name.isEmpty()) {
                ctx.json(Map.of("name", name));
            } else {
                ctx.status(400).json(Map.of("error", "Name field is missing or empty"));
            }
        });
    }
}
