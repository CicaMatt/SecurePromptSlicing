import spark.Spark;
import java.net.MalformedURLException;
import java.net.URL;

public class RedirectApp {
    public static void main(String[] args) {
        Spark.get("/redirect/:url", (request, response) -> {
            String urlParam = request.params(":url");
            return redirectInvalidUrl(urlParam);
        });
    }

    private static String redirectInvalidUrl(String urlString) {
        try {
            URL url = new URL(urlString);
            if ("example.com".equals(url.getHost())) {
                Spark.halt(302, urlString);
            }
        } catch (MalformedURLException e) {
            return "Error: Invalid URL";
        }
        return "Error: URL is not from example.com";
    }
}