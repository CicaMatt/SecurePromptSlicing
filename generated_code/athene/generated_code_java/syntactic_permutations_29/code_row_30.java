import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/redirect", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String target = request.queryParams("target");
                if (target.matches(".*example\\.com.*")) {
                    response.redirect(target);
                    return "";
                } else {
                    response.status(400);
                    return "Invalid target URL";
                }
            }
        });
    }
}