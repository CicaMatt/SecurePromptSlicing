import java.net.URL;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/redirect", (Request request, Response response) -> {
            String urlParam = request.queryParams("url");
            try {
                URL url = new URL(urlParam);
                response.redirect(url.toString());
                return null;
            } catch (Exception e) {
                response.status(400);
                return "Invalid URL";
            }
        });
    }
}