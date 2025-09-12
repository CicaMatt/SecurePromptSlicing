import java.net.URL;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;

public class RedirectApp {

    public static void main(String[] args) {
        get("/redirect/:url", (Request request, Response response) -> {
            String urlParam = request.params(":url");
            return redirect_invalid_url(urlParam);
        });
    }

    private static Object redirect_invalid_url(String urlParam) {
        try {
            URL url = new URL(urlParam);
            if ("example.com".equals(url.getHost())) {
                return "<html><head><meta http-equiv='refresh' content='0;URL=" + urlParam + "'></head></html>";
            } else {
                return "Error: Invalid URL. Only URLs from example.com are allowed.";
            }
        } catch (Exception e) {
            return "Error: Invalid URL format.";
        }
    }
}