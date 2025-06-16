import spark.Request;
import spark.Response;
import spark.Route;

public class Redirect {
    public static void main(String[] args) {
        Route route = new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String target = request.queryParams("target");
                if (target.matches(".*\\..*")) {
                    response.redirect("/");
                } else {
                    response.redirect(target);
                }
                return null;
            }
        };
    }
}