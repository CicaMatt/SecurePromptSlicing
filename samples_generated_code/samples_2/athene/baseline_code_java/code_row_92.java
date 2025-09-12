import java.net.URL;
import spark.Route;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/redirect", (Request req, Response res) -> redirect_invalid_url(req.queryParams("url"), res));
    }

    private static Object redirect_invalid_url(String urlStr, Response res) {
        try {
            URL url = new URL(urlStr);
            String domain = url.getHost();
            if ("example.com".equals(domain)) {
                res.redirect(urlStr);
                return "";
            } else {
                return "Error: Invalid URL";
            }
        } catch (Exception e) {
            return "Error: Invalid URL";
        }
    }
}