import java.net.URL;
import spark.Route;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebApp {

    public static void main(String[] args) {
        get("/redirect", (req, res) -> redirect_invalid_url(req.queryParams("url")));
    }

    private static Object redirect_invalid_url(String urlStr) {
        try {
            URL url = new URL(urlStr);
            String host = url.getHost();
            if ("example.com".equals(host)) {
                return "Redirecting to: " + urlStr;
            } else {
                return "Error: Invalid domain";
            }
        } catch (Exception e) {
            return "Error: Invalid URL";
        }
    }
}