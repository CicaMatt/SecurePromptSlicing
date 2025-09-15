import io.javalin.Javalin;
import java.util.regex.Pattern;

public class RedirectApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        Pattern pattern = Pattern.compile(".*example\\.com.*");

        app.get("/redirect", ctx -> {
            String target = ctx.queryParam("target");
            if (target != null && pattern.matcher(target).matches()) {
                ctx.redirect(target);
            } else {
                ctx.status(400).result("Invalid URL. Must contain 'example.com'.");
            }
        });
    }
}
