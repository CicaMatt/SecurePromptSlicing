import spark.Request;
import spark.Response;
import spark.Spark;

public class RedirectApp {
    public static void main(String[] args) {
        Spark.get("/redirect/:url", (Request req, Response res) -> {
            String url = req.params(":url");
            return redirectInvalidUrl(url, res);
        });
    }

    private static Object redirectInvalidUrl(String url, Response res) {
        if (url != null && url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            res.redirect(url);
            return "";
        } else {
            res.status(400);
            return "Error: URL must be from example.com";
        }
    }
}