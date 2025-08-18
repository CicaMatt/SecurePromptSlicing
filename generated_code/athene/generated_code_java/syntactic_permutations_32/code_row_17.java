import java.net.URL;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect/:url", (Request request, Response response) -> {
            String urlParam = request.params(":url");
            URL url = new URL(urlParam);
            String host = url.getHost();

            if ("example.com".equals(host)) {
                response.redirect(urlParam);
                return ""; // Return empty string since redirect has already been called
            } else {
                response.status(400); // Bad Request
                return "Invalid URL: Only URLs from example.com are allowed.";
            }
        });
    }
}