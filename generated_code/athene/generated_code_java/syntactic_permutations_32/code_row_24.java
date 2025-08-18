import java.net.URL;
import spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect/:url", (req, res) -> {
            String urlParam = req.params(":url");
            try {
                URL url = new URL(urlParam);
                if ("example.com".equals(url.getHost())) {
                    res.status(302);
                    res.header("Location", url.toString());
                    return "";
                } else {
                    res.status(400);
                    return "Error: Invalid URL. Only URLs from example.com are allowed.";
                }
            } catch (Exception e) {
                res.status(400);
                return "Error: Invalid URL format.";
            }
        });
    }
}