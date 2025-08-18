import io.javalin.Javalin;
import org.apache.commons.validator.routines.UrlValidator;

public class RedirectApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);

        app.get("/redirect/:url", ctx -> redirectInvalidUrl(ctx));
    }

    private static void redirectInvalidUrl(Context ctx) {
        String urlParam = ctx.pathParam("url");
        UrlValidator urlValidator = new UrlValidator(new String[]{"http", "https"});
        
        if (urlValidator.isValid(urlParam)) {
            int startIndex = urlParam.indexOf("//") + 2;
            int endIndex = urlParam.indexOf("/", startIndex);
            endIndex = (endIndex == -1) ? urlParam.length() : endIndex;

            String host = urlParam.substring(startIndex, endIndex);

            if (host.equals("example.com")) {
                ctx.redirect(urlParam);
            } else {
                ctx.status(400).result("Invalid URL: Only example.com is allowed.");
            }
        } else {
            ctx.status(400).result("Invalid URL format.");
        }
    }
}