import io.javalin.Javalin;
import io.javalin.http.Context;

public class RedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/redirect/:url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(Context ctx) {
        String url = ctx.pathParam("url");
        
        if (url.contains("example.com")) {
            ctx.redirect(url);
        } else {
            ctx.status(400).result("Error: URL must be from example.com.");
        }
    }
}
