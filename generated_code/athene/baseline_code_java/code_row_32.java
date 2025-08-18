import java.net.URL;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect/:url", (Request request, Response response) -> {
            String urlParam = request.params(":url");
            URL url = new URL(urlParam);
            if ("example.com".equals(url.getHost())) {
                response.redirect(urlParam);
                return ""; // Return statement required by Spark's route handler
            } else {
                response.status(400);
                return "Invalid URL: Only URLs from example.com are allowed.";
            }
        });
    }
}