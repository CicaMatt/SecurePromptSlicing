import java.net.URL;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/redirect", (Request req, Response res) -> {
            String inputUrl = req.queryParams("url");
            URL url = new URL(inputUrl);
            String domain = url.getHost();

            if ("example.com".equals(domain)) {
                res.redirect(inputUrl);
                return "";
            } else {
                res.status(400);
                return "Invalid URL: Only 'example.com' is allowed.";
            }
        });
    }
}