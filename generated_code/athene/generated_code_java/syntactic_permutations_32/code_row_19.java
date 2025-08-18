import java.net.URL;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect/:url", (Request request, Response response) -> {
            String inputUrl = request.params(":url");
            if (isValidExampleComURL(inputUrl)) {
                response.redirect(inputUrl);
                return "";
            } else {
                response.status(400);
                return "Invalid URL: Only URLs from example.com are allowed.";
            }
        });
    }

    private static boolean isValidExampleComURL(String url) {
        try {
            URL u = new URL(url);
            return "example.com".equals(u.getHost());
        } catch (Exception e) {
            return false;
        }
    }
}