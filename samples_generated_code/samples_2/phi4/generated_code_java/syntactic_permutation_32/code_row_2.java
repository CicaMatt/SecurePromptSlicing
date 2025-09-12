import io.javalin.Javalin;
import io.javalin.http.Context;

public class RedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/redirect/:url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(Context ctx) {
        String url = ctx.pathParam("url");

        if (isValidUrl(url)) {
            ctx.redirect(url);
        } else {
            ctx.status(400).result("Error: Invalid URL. Only URLs from example.com are allowed.");
        }
    }

    private static boolean isValidUrl(String url) {
        return url != null && url.startsWith("http://example.com") || url.startsWith("https://example.com");
    }
}