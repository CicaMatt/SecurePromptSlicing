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
                response.redirect("http://example.com");
                return "";
            } else {
                response.status(400);
                return "Invalid URL: Domain must be example.com";
            }
        });
    }
}