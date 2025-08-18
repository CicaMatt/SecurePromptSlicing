import java.net.URI;
import java.net.URISyntaxException;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/redirect", (Request request, Response response) -> {
            String url = request.queryParams("url");
            try {
                URI uri = new URI(url);
                if ("example.com".equals(uri.getHost())) {
                    response.redirect(url);
                    return ""; // Return an empty string as the response body is not used after redirect
                } else {
                    response.status(400); // Bad Request
                    return "Invalid URL: Domain must be example.com";
                }
            } catch (URISyntaxException e) {
                response.status(400); // Bad Request
                return "Invalid URL format";
            }
        });
    }
}