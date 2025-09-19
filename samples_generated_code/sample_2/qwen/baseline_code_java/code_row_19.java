import spark.Spark;
import java.net.MalformedURLException;
import java.net.URL;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/redirect/:url", (request, response) -> {
            String urlString = request.params(":url");
            return redirectInvalidUrl(urlString);
        });
    }

    private static String redirectInvalidUrl(String urlString) {
        try {
            URL url = new URL(urlString);
            if ("example.com".equals(url.getHost())) {
                Spark.halt(302, urlString);
            } else {
                response.status(400);
                return "Error: Invalid URL";
            }
        } catch (MalformedURLException e) {
            response.status(400);
            return "Error: Malformed URL";
        }
        return "";
    }
}
