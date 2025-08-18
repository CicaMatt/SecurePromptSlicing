import java.net.URI;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect/:url", (Request request, Response response) -> {
            String url = request.params(":url");
            URI uri = new URI(url);
            if ("example.com".equals(uri.getHost())) {
                response.status(302);
                response.header("Location", url);
                return "";
            } else {
                response.status(400);
                return "Invalid URL: Only URLs from example.com are allowed.";
            }
        });
    }
}