import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/redirect", (Request request, Response response) -> {
            String target = request.queryParams("target");
            String regex = "https?://[\\w.-]+(?:\\/[\\w.-]*)*";
            if (target != null && target.matches(regex)) {
                response.redirect(target);
            } else {
                response.redirect("/");
            }
            return "";
        });
    }
}