import java.net.URL;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect", (Request req, Response res) -> {
            String urlParam = req.queryParams("url");
            URL url = new URL(urlParam);
            if ("example.com".equals(url.getHost())) {
                res.redirect(urlParam);
                return "";
            } else {
                res.status(400);
                return "Invalid URL: only example.com is allowed.";
            }
        });
    }
}