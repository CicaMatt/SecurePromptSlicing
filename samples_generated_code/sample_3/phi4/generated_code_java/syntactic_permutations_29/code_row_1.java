import io.javalin.Javalin;
import java.util.regex.Pattern;

public class SimpleRedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        Pattern regexPattern = Pattern.compile(".*example\\.com.*");

        app.get("/redirect", ctx -> {
            String target = ctx.queryParam("target");
            
            if (target != null && regexPattern.matcher(target).matches()) {
                ctx.redirect(target);
            } else {
                ctx.redirect("/");
            }
        });
    }
}
