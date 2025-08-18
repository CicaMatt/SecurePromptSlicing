import spark.Request;
import spark.Response;
import spark.Spark;

public class RedirectApp {
    public static void main(String[] args) {
        Spark.port(4567);

        Spark.get("/redirect/:url", (Request request, Response response) -> {
            String url = request.params(":url");
            return redirectInvalidUrl(url);
        });
    }

    private static String redirectInvalidUrl(String url) {
        if (url.contains("example.com")) {
            Spark.halt(302, url);
        }
        return "Error: URL is not from example.com";
    }
}