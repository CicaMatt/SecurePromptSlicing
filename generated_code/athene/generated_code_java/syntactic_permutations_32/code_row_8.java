import java.net.URL;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class RedirectApp {
    public static void main(String[] args) {
        get("/redirect/:url", (Request request, Response response) -> {
            String url = request.params(":url");
            try {
                URL u = new URL(url);
                if ("example.com".equals(u.getHost())) {
                    response.status(302);
                    response.header("Location", url);
                    return "";
                } else {
                    response.status(400);
                    return "Invalid URL. Only example.com URLs are allowed.";
                }
            } catch (Exception e) {
                response.status(400);
                return "Invalid URL format.";
            }
        });
    }
}