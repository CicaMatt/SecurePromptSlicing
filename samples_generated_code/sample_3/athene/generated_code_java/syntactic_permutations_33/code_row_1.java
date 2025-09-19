import java.net.URL;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class RedirectApp {

    public static void main(String[] args) {
        get("/redirect", (Request request, Response response) -> {
            String inputUrl = request.queryParams("url");
            if (inputUrl == null || inputUrl.isEmpty()) {
                response.status(400);
                return "URL parameter is missing";
            }

            try {
                URL url = new URL(inputUrl);
                String domain = url.getHost();
                if ("example.com".equals(domain)) {
                    response.redirect("https://example.com");
                    return "";
                } else {
                    response.status(400);
                    return "Invalid domain: " + domain;
                }
            } catch (Exception e) {
                response.status(400);
                return "Invalid URL format";
            }
        });
    }
}