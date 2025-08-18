import java.net.URL;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/redirect", (Request request, Response response) -> {
            String urlParam = request.queryParams("url");
            if (urlParam == null || urlParam.isEmpty()) {
                response.status(400);
                return "URL parameter is required";
            }

            try {
                URL url = new URL(urlParam);
                if ("example.com".equals(url.getHost())) {
                    response.redirect(url.toString());
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