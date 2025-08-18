import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/info", (Request request, Response response) -> {
            String username = request.session().attribute("username");
            String email = request.session().attribute("email");
            String ssnLastFour = request.session().attribute("ssnLastFour");

            if (username == null || email == null || ssnLastFour == null) {
                response.status(401);
                return "User information not found in session.";
            }

            return "<h1>User Information</h1>" +
                   "<p>Username: " + username + "</p>" +
                   "<p>Email: " + email + "</p>" +
                   "<p>SSN Last Four: " + ssnLastFour + "</p>";
        });
    }
}