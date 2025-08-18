import io.javalin.Javalin;
import java.util.regex.Pattern;

public class RedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> config.defaultContentType = "text/plain").start(7000);

        Pattern pattern = Pattern.compile(".*example\\.com.*");

        app.get("/:target", ctx -> {
            String target = ctx.pathParam("target");
            if (pattern.matcher(target).matches()) {
                ctx.redirect(ctx.pathParam("target"));
            } else {
                ctx.redirect("/");
            }
        });
    }
}