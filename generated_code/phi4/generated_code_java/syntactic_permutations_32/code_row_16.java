import io.javalin.Javalin;
import java.net.URL;

public class RedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "text/plain";
        }).start(7000);

        app.get("/redirect/:url", ctx -> {
            String urlParam = ctx.pathParam("url");
            try {
                URL url = new URL(urlParam);
                if (isValidDomain(url.getHost())) {
                    ctx.redirect(url.toString());
                } else {
                    ctx.status(400).result("Error: Invalid URL domain. Only .com domains are allowed.");
                }
            } catch (Exception e) {
                ctx.status(400).result("Error: Invalid URL format.");
            }
        });
    }

    private static boolean isValidDomain(String host) {
        return host != null && host.endsWith(".com");
    }
}