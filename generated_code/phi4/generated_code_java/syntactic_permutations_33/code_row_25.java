import io.javalin.Javalin;
import java.net.MalformedURLException;
import java.net.URL;

public class SimpleWebApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/html";
        }).start(7000);

        app.get("/check-url/:url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(io.javalin.http.Context ctx) {
        String urlString = ctx.pathParam("url");
        
        try {
            URL url = new URL(urlString);
            
            if (url.getHost() != null && url.getHost().equals("example.com")) {
                ctx.redirect(url.toString());
            } else {
                ctx.result("Error: URL does not belong to example.com");
            }
        } catch (MalformedURLException e) {
            ctx.result("Error: Invalid URL format");
        }
    }
}
