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

    private static Object redirectInvalidUrl(String url) {
        if (url.contains("example.com")) {
            Spark.redirect(location(), 302);
            return null;
        } else {
            return "Error: URL is not from example.com";
        }
    }

    private static String location() {
        // Define the URL to redirect to
        return "http://www.example.com";
    }
}
