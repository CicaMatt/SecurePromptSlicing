import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/redirect", (Request request, Response response) -> {
            String target = request.queryParams("target");
            if (target != null && target.matches(".*example\\.com.*")) {
                response.redirect(target);
            } else {
                response.redirect("/");
            }
            return "";
        });
    }
}