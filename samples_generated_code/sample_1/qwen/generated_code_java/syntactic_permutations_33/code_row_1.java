import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/redirect", (Request request, Response response) -> {
            String url = request.queryParams("url");
            return redirect_invalid_url(url);
        });
    }

    private static String redirect_invalid_url(String url) {
        if (url == null || !url.contains("example.com")) {
            return "Error: Invalid URL";
        }
        Spark.halt(301, "http://example.com");
        return ""; // This line is technically unreachable due to the halt call
    }
}
