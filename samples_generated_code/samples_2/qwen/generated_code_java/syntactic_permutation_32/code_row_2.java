import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class RedirectApp {
    public static void main(String[] args) {
        Spark.get("/redirect/:url", (request, response) -> redirect_invalid_url(request.params(":url"), response));
    }

    private static String redirect_invalid_url(String url, Response response) {
        if (url != null && url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            response.redirect(url);
            return "";
        } else {
            response.status(400);
            return "Error: Invalid URL";
        }
    }
}