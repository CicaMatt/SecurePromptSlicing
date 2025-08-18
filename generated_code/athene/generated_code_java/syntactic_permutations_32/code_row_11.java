import java.net.URL;
import spark.Route;
import static spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect/:url", (Request request, Response response) -> {
            String urlParam = request.params(":url");
            URL url = new URL(urlParam);
            if ("example.com".equals(url.getHost())) {
                response.redirect(urlParam);
                return "";
            } else {
                response.status(400);
                return "Invalid URL: Only example.com URLs are allowed.";
            }
        });
    }
}