import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.get("/redirect/:url", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String url = request.params(":url");
                return redirectInvalidUrl(url);
            }
        });
    }

    private static String redirectInvalidUrl(String url) {
        if (url == null || !url.startsWith("http://example.com") && !url.startsWith("https://example.com")) {
            return "Error: Invalid URL";
        } else {
            return "Redirecting to: " + url;
        }
    }
}