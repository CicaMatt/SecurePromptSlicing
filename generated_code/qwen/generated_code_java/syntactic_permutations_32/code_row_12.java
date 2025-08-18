import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.get("/redirect/:url", (request, response) -> redirectInvalidUrl(request.params(":url"), response));
    }

    private static String redirectInvalidUrl(String url, Response response) {
        if (isValidUrl(url)) {
            response.redirect(url);
            return "";
        } else {
            response.status(400);
            return "Error: Invalid URL";
        }
    }

    private static boolean isValidUrl(String url) {
        return url != null && !url.isEmpty() && url.matches("^(https?|ftp)://.*$");
    }
}