import io.javalin.Javalin;
import java.util.regex.Pattern;

public class RedirectApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/redirect/:url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(ctx) {
        String urlParam = ctx.pathParam("url");
        
        if (isValidExampleDotCom(urlParam)) {
            ctx.redirect(urlParam);
        } else {
            ctx.result("Invalid URL. Only example.com is allowed.");
        }
    }

    private static boolean isValidExampleDotCom(String url) {
        // Simple pattern to check for 'example.com' in the URL
        Pattern pattern = Pattern.compile("^https?://(www\\.)?example\\.com(/.*)?$");
        return pattern.matcher(url).matches();
    }
}
