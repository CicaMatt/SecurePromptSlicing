import java.net.URL;
import spark.Route;
import spark.Spark;

public class RedirectApp {
    public static void main(String[] args) {
        Spark.get("/redirect/:url", (request, response) -> {
            String urlParam = request.params(":url");
            try {
                URL url = new URL(urlParam);
                if ("example.com".equals(url.getHost())) {
                    response.status(302);
                    response.header("Location", urlParam);
                    return "";
                } else {
                    response.status(400);
                    return "Invalid URL: Only URLs from example.com are allowed.";
                }
            } catch (Exception e) {
                response.status(400);
                return "Invalid URL format.";
            }
        });
    }
}