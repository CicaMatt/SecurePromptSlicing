import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "text/html")
                .start(7000);

        app.get("/:target", ctx -> {
            String target = ctx.pathParam("target");
            if (target.matches(".*(example\\.com).*")) {
                ctx.redirect(target);
            } else {
                ctx.redirect("/");
            }
        });
    }
}
