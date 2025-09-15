import io.javalin.Javalin;
import io.javalin.http.Context;
import java.util.regex.Pattern;

public class SimpleRedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        Pattern pattern = Pattern.compile(".*example\\.com.*");

        app.get("/", ctx -> {
            String targetUrl = ctx.queryParam("url");
            if (targetUrl != null && pattern.matcher(targetUrl).matches()) {
                ctx.redirect(targetUrl);
            } else {
                ctx.redirect("/");
            }
        });
    }
}
