import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class RedirectApp {
    public static void main(String[] args) {
        Spark.get("/redirect/:url", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String url = request.params(":url");
                return redirectInvalidUrl(url);
            }
        });
    }

    private static String redirectInvalidUrl(String url) {
        if (url != null && url.contains("example.com")) {
            Spark.halt(302, url);
        } else {
            return "Error: URL is not from example.com";
        }
        return "";
    }
}