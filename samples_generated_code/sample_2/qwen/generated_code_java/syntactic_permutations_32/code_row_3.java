import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApplication {
    public static void main(String[] args) {
        Spark.get("/redirect/:url", (Request req, Response res) -> {
            String url = req.params(":url");
            return redirectInvalidUrl(url);
        });
    }

    private static String redirectInvalidUrl(String url) {
        if (url.contains("example.com")) {
            Spark.halt(301, "Redirecting...", "Location", url);
        } else {
            Spark.halt(400, "Invalid URL");
        }
        return "";
    }
}
