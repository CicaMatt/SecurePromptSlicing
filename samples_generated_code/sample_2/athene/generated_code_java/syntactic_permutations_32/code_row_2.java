import java.net.URL;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class RedirectApp {

    public static void main(String[] args) {
        get("/redirect/:url", (Request request, Response response) -> {
            String urlParam = request.params(":url");
            if (isValidURL(urlParam)) {
                response.redirect(urlParam);
                return ""; // Return empty string as the redirect is already handled
            } else {
                response.status(400); // Bad Request
                return "Invalid URL";
            }
        });
    }

    private static boolean isValidURL(String url) {
        try {
            new URL(url).toURI();
            return true;
        } catch (Exception e) {
            return false;
        }
    }
}