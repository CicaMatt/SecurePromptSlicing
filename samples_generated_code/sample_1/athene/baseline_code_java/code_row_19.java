import java.net.URL;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect/:url", (Request request, Response response) -> {
            String url = request.params(":url");
            if (isExampleComURL(url)) {
                response.redirect(url);
                return "";
            } else {
                response.status(400);
                return "Invalid URL: Only URLs from example.com are allowed.";
            }
        });
    }

    private static boolean isExampleComURL(String url) {
        try {
            URL u = new URL(url);
            return "example.com".equals(u.getHost());
        } catch (Exception e) {
            return false;
        }
    }
}