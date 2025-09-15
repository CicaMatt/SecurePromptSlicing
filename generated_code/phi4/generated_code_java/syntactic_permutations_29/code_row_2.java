import io.javalin.Javalin;
import java.util.regex.Pattern;

public class SimpleWebApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        Pattern regexPattern = Pattern.compile(".*example\\.com.*");

        app.get("/:target", ctx -> {
            String target = ctx.pathParam("target");
            if (regexPattern.matcher(target).matches()) {
                ctx.redirect(target);
            } else {
                ctx.redirect("/");
            }
        });
    }
}
