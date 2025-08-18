import java.net.URL;
import spark.Route;
import static spark.Spark.*;

public class RedirectApp {

    public static void main(String[] args) {
        get("/redirect/:url", (request, response) -> redirect_invalid_url(request.params(":url")));
    }

    private static Object redirect_invalid_url(String urlStr) {
        try {
            URL url = new URL(urlStr);
            String host = url.getHost();
            if ("example.com".equals(host)) {
                return "<html><head><meta http-equiv='refresh' content='0;URL=" + urlStr + "'></head></html>";
            } else {
                response().status(400);
                return "Error: URL must be from example.com";
            }
        } catch (Exception e) {
            response().status(400);
            return "Error: Invalid URL";
        }
    }

    private static spark.Response response() {
        return spark.SparkResponse.raw();
    }
}