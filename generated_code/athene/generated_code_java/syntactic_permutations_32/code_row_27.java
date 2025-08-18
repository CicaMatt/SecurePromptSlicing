import java.net.URL;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;

public class RedirectApp {

    public static void main(String[] args) {
        get("/redirect/:url", (Request req, Response res) -> redirect_invalid_url(req.params(":url")), String.class);
    }

    private static String redirect_invalid_url(String urlStr) {
        try {
            URL url = new URL(urlStr);
            if ("example.com".equals(url.getHost())) {
                return "Redirecting to: " + urlStr;
            } else {
                return "<h1>403 Forbidden</h1>";
            }
        } catch (Exception e) {
            return "<h1>400 Bad Request</h1>";
        }
    }
}