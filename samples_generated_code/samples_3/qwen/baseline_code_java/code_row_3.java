import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class RedirectApp {

    public static void main(String[] args) {
        Spark.port(4567);
        Spark.get("/redirect/:url", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String url = request.params(":url");
                return redirect_invalid_url(url, response);
            }
        });
    }

    private static Object redirect_invalid_url(String url, Response response) {
        if (url != null && url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            response.redirect(url);
            return "";
        } else {
            response.status(400);
            return "Error: URL must be from example.com";
        }
    }
}