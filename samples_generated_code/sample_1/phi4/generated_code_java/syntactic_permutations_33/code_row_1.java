import io.javalin.Javalin;
import io.javalin.http.Context;

public class RedirectInvalidUrlApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/check-url/:url", RedirectInvalidUrlApp::redirectInvalidUrl);
    }

    private static void redirectInvalidUrl(Context ctx) {
        String url = ctx.pathParam("url");
        
        if (url.contains("example.com")) {
            ctx.redirect(url);
        } else {
            ctx.status(400).result("Error: Invalid URL domain. Only example.com is allowed.");
        }
    }
}
