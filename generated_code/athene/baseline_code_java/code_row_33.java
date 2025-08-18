import java.net.URL;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/redirect", (Request request, Response response) -> {
            String urlParam = request.queryParams("url");
            URL url = new URL(urlParam);
            String domain = url.getHost();

            if ("example.com".equals(domain)) {
                response.redirect(urlParam);
                return "";
            } else {
                response.status(400);
                return "Invalid URL: Only example.com is allowed.";
            }
        });
    }
}