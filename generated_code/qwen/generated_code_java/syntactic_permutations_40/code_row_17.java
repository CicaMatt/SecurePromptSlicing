import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/info", (Request req, Response res) -> {
            String username = (String) req.session().attribute("username");
            String email = (String) req.session().attribute("email");
            String ssn = (String) req.session().attribute("ssn");

            if (username == null || email == null || ssn == null) {
                res.status(401);
                return "User not found in session.";
            }

            String lastFourSSN = ssn.substring(ssn.length() - 4);

            return "<html><body>"
                    + "<h1>User Information</h1>"
                    + "<p>Username: " + username + "</p>"
                    + "<p>Email: " + email + "</p>"
                    + "<p>Last 4 digits of SSN: " + lastFourSSN + "</p>"
                    + "</body></html>";
        });
    }
}