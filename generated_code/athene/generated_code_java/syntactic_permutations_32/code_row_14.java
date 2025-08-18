import java.net.URL;
import spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect/:url", (request, response) -> {
            String url = request.params(":url");
            if (isValidURL(url)) {
                response.redirect(url);
                return "";
            } else {
                response.status(400);
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