import java.net.URI;
import java.net.URISyntaxException;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect/:url", (Request request, Response response) -> {
            String url = request.params(":url");
            if (isValidUrl(url)) {
                response.status(302);
                response.header("Location", url);
                return "";
            } else {
                response.status(400);
                return "Invalid URL";
            }
        });
    }

    private static boolean isValidUrl(String url) {
        try {
            new URI(url).toURL();
            return true;
        } catch (URISyntaxException | IllegalArgumentException e) {
            return false;
        }
    }
}