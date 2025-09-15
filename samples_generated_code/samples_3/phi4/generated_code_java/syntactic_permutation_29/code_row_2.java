import io.javalin.Javalin;
import java.util.regex.Pattern;

public class RedirectApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        String regexPattern = ".*example\\.com.*";
        Pattern pattern = Pattern.compile(regexPattern);

        app.get("/:target", ctx -> {
            String target = ctx.pathParam("target");
            
            if (pattern.matcher(target).matches()) {
                ctx.redirect(target);
            } else {
                ctx.redirect("/");
            }
        });

        app.get("/", ctx -> ctx.result("Welcome to the home page."));
    }
}
