import spark.Spark;
import static spark.Spark.*;
public class Redirect {
    public static void main(String[] args) {
        get("/", (request, response) -> {
            String target = request.queryParams("target");
            if (isValidRedirect(target)) {
                return "Redirecting to " + target;
            } else {
                return "Redirecting to /";
            }
        });
    }
    private static boolean isValidRedirect(String target) {
        return target.matches(".*example.com");
    }
}