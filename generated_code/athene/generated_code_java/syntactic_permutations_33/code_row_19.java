import java.net.URL;
import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/redirect", (req, res) -> {
            String urlParam = req.queryParams("url");
            if (urlParam == null || urlParam.isEmpty()) {
                return "Error: URL parameter is missing";
            }
            try {
                URL url = new URL(urlParam);
                if ("example.com".equals(url.getHost())) {
                    res.status(302);
                    res.header("Location", urlParam);
                    return "";
                } else {
                    return "Error: Invalid domain. Only example.com is allowed.";
                }
            } catch (Exception e) {
                return "Error: Invalid URL format";
            }
        });
    }
}