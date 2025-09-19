import io.javalin.Javalin;
import org.apache.commons.validator.routines.UrlValidator;

public class RedirectApp {
    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.get("/redirect/:url", ctx -> {
            String urlString = ctx.pathParam("url");
            
            if (isValidUrl(urlString)) {
                ctx.redirect(urlString);
            } else {
                ctx.status(400).result("Invalid URL");
            }
        });
    }

    private static boolean isValidUrl(String url) {
        UrlValidator urlValidator = new UrlValidator(new String[]{"http", "https"});
        return urlValidator.isValid(url);
    }
}