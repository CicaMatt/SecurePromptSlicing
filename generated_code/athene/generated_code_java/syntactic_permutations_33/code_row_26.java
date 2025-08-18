import java.net.URL;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect", (Request request, Response response) -> {
            String urlParam = request.queryParams("url");
            if (urlParam == null || urlParam.isEmpty()) {
                response.status(400);
                return "URL parameter is missing";
            }

            try {
                URL url = new URL(urlParam);
                String domain = url.getHost();
                if ("example.com".equalsIgnoreCase(domain)) {
                    response.redirect(urlParam, 302);
                    return "";
                } else {
                    response.status(400);
                    return "Invalid domain: only example.com is allowed";
                }
            } catch (Exception e) {
                response.status(400);
                return "Invalid URL format";
            }
        });
    }
}