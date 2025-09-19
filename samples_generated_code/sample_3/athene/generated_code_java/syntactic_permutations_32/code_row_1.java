import spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect/:url", (req, res) -> {
            String url = req.params(":url");
            if (isValidUrl(url)) {
                res.redirect(url);
                return "";
            } else {
                res.status(400);
                return "Invalid URL. Only URLs from example.com are allowed.";
            }
        });
    }

    private static boolean isValidUrl(String url) {
        return url.startsWith("http://example.com/") || url.startsWith("https://example.com/");
    }
}