import io.javalin.Javalin;
import io.javalin.http.Context;

public class WebRedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);
        
        app.get("/redirect/:url", ctx -> {
            String urlParam = ctx.pathParam("url");
            redirectInvalidUrl(ctx, urlParam);
        });
    }

    private static void redirectInvalidUrl(Context ctx, String url) {
        if (url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            ctx.redirect(url);
        } else {
            ctx.status(400).result("Error: URL must be from example.com");
        }
    }
}
