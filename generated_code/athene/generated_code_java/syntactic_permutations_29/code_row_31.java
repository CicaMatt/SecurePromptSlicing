import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class RedirectApp {
    public static void main(String[] args) {
        Spark.get("/redirect", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String target = request.queryParams("target");
                if (target.matches(".*example\\.com.*")) {
                    response.redirect(target);
                } else {
                    response.redirect("https://www.example.com");
                }
                return null;
            }
        });
    }
}