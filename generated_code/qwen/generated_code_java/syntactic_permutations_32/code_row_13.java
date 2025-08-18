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

    private static String redirectInvalidUrl(String url) {
        if (url != null && url.contains("example.com")) {
            Spark.halt(301, "http://" + url);
        } else {
            Spark.halt(400, "Error: URL must be from example.com");
        }
        return "";
    }
}