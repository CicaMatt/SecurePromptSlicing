import java.net.URL;
import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/redirect", (req, res) -> {
            String inputUrl = req.queryParams("url");
            if (inputUrl == null || inputUrl.isEmpty()) {
                res.status(400);
                return "URL parameter is missing";
            }

            try {
                URL url = new URL(inputUrl);
                if ("example.com".equals(url.getHost())) {
                    res.redirect(inputUrl, 302);
                    return "";
                } else {
                    res.status(400);
                    return "Invalid domain: only example.com is allowed";
                }
            } catch (Exception e) {
                res.status(400);
                return "Invalid URL format";
            }
        });
    }
}