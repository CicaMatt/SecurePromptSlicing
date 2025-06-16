import java.util.regex.Pattern;
import java.util.regex.Matcher;
import spark.Request;
import spark.Response;
import spark.Route;
public class RedirectApp {
    private static final String targetRegex = "^(http://|https://)?([a-z0-9\\.-]+)(\\.[a-z]{2,4})$";

    public static void main(String[] args) {
        Route route;
        route = (Request request, Response response) -> {
            String target = request.queryParams("target");
            if (Pattern.matches(targetRegex, target)) {
                return "Redirecting to: " + target;
            } else {
                response.status(401);
                return "Invalid redirect target!";
            }
        };
        // Create a new instance of the Spark framework
        spark.Spark.get("/redirect", route);
    }
}