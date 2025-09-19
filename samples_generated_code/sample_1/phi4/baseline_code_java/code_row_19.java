import io.javalin.Javalin;
import io.javalin.http.Context;

public class RedirectApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/redirect/:url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(Context ctx) {
        String urlParam = ctx.pathParam("url");
        
        if (urlParam.startsWith("http://example.com") || urlParam.startsWith("https://example.com")) {
            ctx.redirect(urlParam);
        } else {
            ctx.status(400).result("Error: URL must be from example.com.");
        }
    }
}
