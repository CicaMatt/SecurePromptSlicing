import spark.Spark;
import java.net.MalformedURLException;
import java.net.URL;

public class RedirectApp {
    public static void main(String[] args) {
        Spark.get("/redirect/:url", (request, response) -> {
            String urlString = request.params(":url");
            return redirect_invalid_url(urlString);
        });
    }

    private static String redirect_invalid_url(String urlString) {
        try {
            URL url = new URL(urlString);
            if ("example.com".equals(url.getHost())) {
                Spark.halt(302, urlString);
            } else {
                return "Error: Invalid URL";
            }
        } catch (MalformedURLException e) {
            return "Error: Malformed URL";
        }
        return "";
    }
}