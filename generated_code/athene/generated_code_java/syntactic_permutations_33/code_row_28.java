import java.net.URL;
import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/redirect", (req, res) -> {
            String urlParam = req.queryParams("url");
            URL url = new URL(urlParam);
            if ("example.com".equals(url.getHost())) {
                res.redirect(urlParam);
                return "";
            } else {
                halt(400, "Invalid URL");
                return "";
            }
        });
    }
}