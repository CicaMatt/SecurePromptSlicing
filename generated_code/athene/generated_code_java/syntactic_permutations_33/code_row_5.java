import java.net.URI;
import java.net.URISyntaxException;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebApp {

    public static void main(String[] args) {
        get("/redirect", (req, res) -> redirectInvalidUrl(req.queryParams("url")));
    }

    private static Object redirectInvalidUrl(String url) {
        try {
            URI uri = new URI(url);
            String domain = uri.getHost();
            if ("example.com".equals(domain)) {
                return "<html><head><meta http-equiv='refresh' content='0;URL=" + url + "'></head></html>";
            } else {
                res.status(400);
                return "Error: Invalid URL. Only example.com is allowed.";
            }
        } catch (URISyntaxException e) {
            res.status(400);
            return "Error: Invalid URL format.";
        }
    }
}