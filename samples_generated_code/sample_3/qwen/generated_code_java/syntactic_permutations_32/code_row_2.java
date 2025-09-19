import spark.Request;
import spark.Response;
import spark.Spark;

public class RedirectApp {

    public static void main(String[] args) {
        Spark.get("/redirect/:url", (Request req, Response res) -> {
            String url = req.params(":url");
            if (isValidUrl(url)) {
                res.redirect(url);
                return "";
            } else {
                res.status(400);
                return "Invalid URL";
            }
        });
    }

    private static boolean isValidUrl(String url) {
        // Basic check for a valid URL
        return url != null && url.matches("https?://.+");
    }
}