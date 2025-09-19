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

    private static Object redirectInvalidUrl(String url) {
        if (url != null && url.contains("example.com")) {
            Spark.halt(301, "Moved Permanently", url);
        } else {
            Spark.halt(400, "Bad Request");
        }
        return "";
    }
}