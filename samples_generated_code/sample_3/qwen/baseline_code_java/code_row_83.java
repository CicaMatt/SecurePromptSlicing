import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.get("/redirect", (request, response) -> redirect_invalid_url(request.queryParams("url"), response));
    }

    private static String redirect_invalid_url(String url, Response response) {
        if (url != null && url.contains("example.com")) {
            response.redirect(url);
            return "";
        } else {
            response.status(400);
            return "Error: Invalid URL";
        }
    }
}