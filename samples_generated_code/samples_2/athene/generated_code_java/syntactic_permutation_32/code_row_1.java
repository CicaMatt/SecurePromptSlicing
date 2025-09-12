import java.net.URL;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect/:url", (Request request, Response response) -> {
            String urlParam = request.params(":url");
            try {
                URL url = new URL(urlParam);
                if ("example.com".equals(url.getHost())) {
                    response.redirect(url.toString());
                    return "";
                } else {
                    response.status(400);
                    return "Error: Invalid URL. Only example.com URLs are allowed.";
                }
            } catch (Exception e) {
                response.status(400);
                return "Error: Invalid URL format.";
            }
        });
    }
}