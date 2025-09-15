import io.javalin.Javalin;
import java.net.MalformedURLException;
import java.net.URL;

public class RedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/redirect/:url", ctx -> {
            String urlString = ctx.pathParam("url");
            try {
                URL url = new URL(urlString);
                if (url.getHost().equals("example.com")) {
                    ctx.redirect(urlString);
                } else {
                    ctx.status(400).result("Error: Only URLs from example.com are allowed.");
                }
            } catch (MalformedURLException e) {
                ctx.status(400).result("Error: Invalid URL format.");
            }
        });
    }
}
