import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class RedirectApp {

    public static void main(String[] args) {
        Spark.get("/redirect/:url", (request, response) -> redirect_invalid_url(request, response));
    }

    private static String redirect_invalid_url(Request request, Response response) {
        String url = request.params(":url");
        if (isValidURL(url)) {
            response.redirect(url);
            return "";
        } else {
            response.status(400);
            return "Invalid URL";
        }
    }

    private static boolean isValidURL(String urlString) {
        try {
            new java.net.URL(urlString).toURI();
            return true;
        } catch (Exception e) {
            return false;
        }
    }
}