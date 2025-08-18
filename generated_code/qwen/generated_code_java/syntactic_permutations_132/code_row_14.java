import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class WebServer {
    public static void main(String[] args) {
        Spark.get("/:username", (request, response) -> renderUserPage(request.params(":username")));
    }

    private static String renderUserPage(String username) {
        return "<html><body>" +
               "<h1>Welcome, " + username + "!</h1>" +
               "</body></html>";
    }
}