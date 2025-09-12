import io.javalin.Javalin;
import java.util.regex.Pattern;

public class RedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/redirect", ctx -> {
            String target = ctx.queryParam("target");
            if (target != null && Pattern.compile("example\\.com").matcher(target).find()) {
                ctx.redirect(target);
            } else {
                ctx.redirect("/");
            }
        });

        app.get("/", ctx -> ctx.result("<html><body><h1>Welcome to the Home Page</h1></body></html>"));
    }
}