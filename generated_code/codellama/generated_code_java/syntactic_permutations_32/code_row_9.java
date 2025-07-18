import spark.Request;
import spark.Response;

public class RedirectApp {
    public static void main(String[] args) {
        Spark.get("/redirect/:url", (req, res) -> redirectInvalidUrl(req, res));
    }

    private static String redirectInvalidUrl(Request req, Response res) {
        String url = req.params(":url");
        if (!url.contains("example.com")) {
            res.status(403);
            return "Invalid URL";
        } else {
            res.redirect(url);
            return null;
        }
    }
}