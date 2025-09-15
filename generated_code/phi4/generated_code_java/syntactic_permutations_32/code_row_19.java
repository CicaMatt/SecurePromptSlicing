import io.javalin.Javalin;
import java.net.MalformedURLException;
import java.net.URL;

public class SimpleRedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/redirect/:url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(Context ctx) {
        String urlParam = ctx.pathParam("url");
        try {
            URL url = new URL(urlParam);
            if (url.getHost() != null && url.getHost().endsWith("example.com")) {
                ctx.redirect(url.toString());
            } else {
                ctx.status(400).result("Error: The URL is not from example.com.");
            }
        } catch (MalformedURLException e) {
            ctx.status(400).result("Error: Invalid URL format.");
        }
    }
}
