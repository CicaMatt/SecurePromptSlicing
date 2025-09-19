import io.javalin.Javalin;
import io.javalin.http.Context;

public class HelloDecorator {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/hello/:username", ctx -> {
            String username = ctx.pathParam("username");
            ctx.render("templates/hello.html", Map.of("username", username));
        });
    }
}
