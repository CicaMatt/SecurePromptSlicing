import java.net.URL;
import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/redirect", (req, res) -> {
            String urlParam = req.queryParams("url");
            URL url = new URL(urlParam);
            if ("example.com".equals(url.getHost())) {
                res.redirect("https://example.com");
                return "";
            } else {
                res.status(400);
                return "Invalid URL domain";
            }
        });
    }
}