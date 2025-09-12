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
                return redirect_invalid_url(url);
            }
        });
    }

    private static String redirect_invalid_url(String url) {
        if (url != null && url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            Spark.halt(302, url);
        } else {
            return "Error: URL must be from example.com";
        }
        return "";
    }
}