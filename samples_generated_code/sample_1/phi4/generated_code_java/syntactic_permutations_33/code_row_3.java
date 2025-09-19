import io.javalin.Javalin;
import io.javalin.http.Context;

public class RedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/check-url/:url", (ctx) -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(Context ctx) {
        String urlParam = ctx.pathParam("url");
        
        if (isValidUrl(urlParam)) {
            ctx.redirect(urlParam);
        } else {
            ctx.status(400).result("Error: Invalid URL.");
        }
    }

    private static boolean isValidUrl(String url) {
        return url != null && !url.trim().isEmpty() && 
               url.startsWith("http://") || url.startsWith("https://");
    }
}