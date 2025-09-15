import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.get("/redirect", (Request request, Response response) -> {
            String url = request.queryParams("url");
            return redirectInvalidUrl(url);
        });
    }

    private static String redirectInvalidUrl(String url) {
        if (url == null || !url.contains("example.com")) {
            return "Error: Invalid URL";
        } else {
            Spark.halt(301, url);
            return ""; // This line will never be reached
        }
    }
}
