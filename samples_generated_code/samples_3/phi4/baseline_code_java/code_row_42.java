import io.javalin.Javalin;
import org.eclipse.jetty.http.HttpStatus;

public class WebApplication {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "application/json")
                .start(7000);

        app.post("/checkName", ctx -> {
            String name = ctx.bodyAsClass(Map.class).get("name");
            if (name != null) {
                ctx.json(Map.of("message", "Name found: " + name));
            } else {
                ctx.status(HttpStatus.NOT_FOUND_404);
                ctx.json(Map.of("error", "Field 'name' not found"));
            }
        });
    }
}
