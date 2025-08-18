import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApplication {

    public static void main(String[] args) {
        Spark.get("/redirect", (Request request, Response response) -> {
            String url = request.queryParams("url");
            return redirectInvalidUrl(url);
        });
    }

    private static Object redirectInvalidUrl(String url) {
        if (url == null || !url.contains("example.com")) {
            return "Error: Invalid URL";
        } else {
            Spark.halt(302, url);
            return "";
        }
    }
}