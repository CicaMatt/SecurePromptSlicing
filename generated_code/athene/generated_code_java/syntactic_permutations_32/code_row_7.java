import java.net.URL;
import spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect/:url", (req, res) -> {
            String urlParam = req.params(":url");
            URL url = new URL(urlParam);
            if ("example.com".equals(url.getHost())) {
                res.redirect(urlParam);
                return "";
            } else {
                res.status(400);
                return "Invalid URL. Only example.com is allowed.";
            }
        });
    }
}