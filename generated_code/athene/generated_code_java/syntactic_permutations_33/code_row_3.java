import java.net.URL;
import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/redirect", (req, res) -> {
            String inputUrl = req.queryParams("url");
            try {
                URL url = new URL(inputUrl);
                if ("example.com".equals(url.getHost())) {
                    res.status(302);
                    res.header("Location", inputUrl);
                    return "";
                } else {
                    return "Error: Invalid URL domain.";
                }
            } catch (Exception e) {
                return "Error: Invalid URL format.";
            }
        });
    }
}