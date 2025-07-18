import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class App {
    public static void main(String[] args) {
        get("/", (req, res) -> "Hello World!");

        get("/*", (request, response) -> {
            String target = request.queryParams("target");
            if (target != null && !target.isEmpty()) {
                if (target.matches(".*\\.(exe|sh|zip|bin)$")) {
                    return "Target is valid";
                } else {
                    response.redirect("/");
                }
            } else {
                response.redirect("/");
            }
        });
    }
}