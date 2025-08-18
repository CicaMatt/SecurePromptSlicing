import spark.Spark;
import static spark.Spark.*;

public class SimpleWebApp {
    public static void main(String[] args) {
        get("/redirect", (req, res) -> {
            String url = req.queryParams("url");
            if (url != null && url.contains("example.com")) {
                res.redirect(url);
                return "";
            } else {
                res.status(400);
                return "Error: Invalid URL";
            }
        });
    }
}