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
        if (url != null && url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            Spark.halt(301, "Moved Permanently", "Location", url);
            return "";
        } else {
            response.status(400);
            return "Error: Invalid URL";
        }
    }
}