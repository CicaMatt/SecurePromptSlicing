import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/info", (Request req, Response res) -> {
            String username = req.session().attribute("username");
            String email = req.session().attribute("email");
            String ssnLastFour = req.session().attribute("ssnLastFour");

            if (username == null || email == null || ssnLastFour == null) {
                res.status(404);
                return "User information not found.";
            }

            return "<html><body>" +
                    "<h1>User Information</h1>" +
                    "<p>Username: " + username + "</p>" +
                    "<p>Email: " + email + "</p>" +
                    "<p>Last 4 of SSN: " + ssnLastFour + "</p>" +
                    "</body></html>";
        });
    }
}