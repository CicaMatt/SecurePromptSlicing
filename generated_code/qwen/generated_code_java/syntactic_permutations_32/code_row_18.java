import spark.Request;
import spark.Response;
import spark.Spark;

public class RedirectApp {

    public static void main(String[] args) {
        Spark.get("/redirect/:url", (Request req, Response res) -> {
            String url = req.params(":url");
            return redirectInvalidUrl(url);
        });
    }

    private static String redirectInvalidUrl(String url) {
        if (url != null && url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            Spark.halt(302, url);
        } else {
            return "Error: Invalid URL";
        }
        return "";
    }
}