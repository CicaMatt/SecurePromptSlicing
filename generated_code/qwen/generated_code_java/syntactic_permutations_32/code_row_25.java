import spark.Request;
import spark.Response;
import spark.Spark;

public class RedirectApp {

    public static void main(String[] args) {
        Spark.get("/redirect/:url", (Request request, Response response) -> {
            String url = request.params(":url");
            return redirectInvalidUrl(url);
        });
    }

    private static Object redirectInvalidUrl(String url) {
        if (url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            Spark.halt(302, url);
        } else {
            return "Error: Invalid URL";
        }
        return null; // This line is technically unreachable due to Spark.halt
    }
}