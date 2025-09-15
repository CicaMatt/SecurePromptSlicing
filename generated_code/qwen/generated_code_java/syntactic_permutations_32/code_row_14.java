import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class RedirectApp {

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
        if (isValidURL(url)) {
            Spark.halt(302, url);
            return null; // This line will never be reached because of halt
        } else {
            return "Error: Invalid URL";
        }
    }

    private static boolean isValidURL(String url) {
        try {
            new java.net.URL(url).toURI();
            return true;
        } catch (Exception e) {
            return false;
        }
    }
}
