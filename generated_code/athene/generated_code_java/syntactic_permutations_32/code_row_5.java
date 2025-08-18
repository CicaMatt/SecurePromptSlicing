import java.net.URL;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class RedirectController {

    public static void main(String[] args) {
        get("/redirect/:url", (Request request, Response response) -> {
            String urlParam = request.params(":url");
            URL url = new URL(urlParam);
            String host = url.getHost();

            if ("example.com".equals(host)) {
                response.redirect(urlParam);
                return "";
            } else {
                response.status(400);
                return "Invalid URL: Only example.com is allowed.";
            }
        });
    }
}