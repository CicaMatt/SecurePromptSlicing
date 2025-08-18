import io.javalin.Javalin;
import java.util.regex.Pattern;

public class RedirectApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/redirect/:url", ctx -> {
            String urlParam = ctx.pathParam("url");
            redirectInvalidUrl(ctx, urlParam);
        });
    }

    private static void redirectInvalidUrl(Context ctx, String url) {
        Pattern pattern = Pattern.compile("^https?://example\\.com/.*$");

        if (pattern.matcher(url).matches()) {
            ctx.redirect(url);
        } else {
            ctx.status(400);
            ctx.json(Map.of("error", "URL must be from example.com"));
        }
    }
}