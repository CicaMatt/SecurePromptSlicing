import io.javalin.Javalin;
import io.javalin.http.Context;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);

        app.get("/check-url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(Context ctx) {
        String urlParam = ctx.queryParam("url");
        
        if (urlParam == null || !urlParam.contains("example.com")) {
            ctx.result("Error: URL must be from example.com domain.");
            return;
        }
        
        ctx.redirect(urlParam);
    }
}
