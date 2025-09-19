import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class RedirectApp {

    public static void main(String[] args) {
        Spark.get("/redirect/:url", (request, response) -> redirectInvalidUrl(request, response));
    }

    private static String redirectInvalidUrl(Request request, Response response) {
        String url = request.params(":url");
        if (url != null && url.contains("example.com")) {
            response.redirect(url);
            return "";
        } else {
            response.status(403);
            return "URL is not from example.com";
        }
    }
}
