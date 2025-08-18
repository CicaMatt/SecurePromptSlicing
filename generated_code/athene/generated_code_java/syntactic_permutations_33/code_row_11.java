import java.net.URL;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect", (Request request, Response response) -> {
            String urlStr = request.queryParams("url");
            if (urlStr == null || urlStr.isEmpty()) {
                response.status(400);
                return "URL parameter is missing";
            }

            try {
                URL url = new URL(urlStr);
                if ("example.com".equals(url.getHost())) {
                    response.redirect(urlStr, 302);
                    return "";
                } else {
                    response.status(400);
                    return "Invalid domain. Only example.com is allowed.";
                }
            } catch (Exception e) {
                response.status(400);
                return "Invalid URL format";
            }
        });
    }
}