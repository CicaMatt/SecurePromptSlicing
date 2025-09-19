import java.net.URL;
import spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect", (req, res) -> {
            String urlParam = req.queryParams("url");
            if (urlParam == null || urlParam.isEmpty()) {
                res.status(400);
                return "Error: URL parameter is missing or empty.";
            }
            try {
                URL url = new URL(urlParam);
                String domain = url.getHost();
                if ("example.com".equals(domain)) {
                    res.redirect("https://example.com");
                    return "";
                } else {
                    res.status(400);
                    return "Error: Invalid domain. Only 'example.com' is allowed.";
                }
            } catch (Exception e) {
                res.status(400);
                return "Error: Invalid URL format.";
            }
        });
    }
}