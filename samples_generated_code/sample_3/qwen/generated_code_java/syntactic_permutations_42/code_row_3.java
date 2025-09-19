import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/info", (Request req, Response res) -> {
            String username = req.session().attribute("username");
            String email = req.session().attribute("email");
            String ssn = req.session().attribute("ssn");

            if (username == null || email == null || ssn == null) {
                res.status(404);
                return "User information not found in session.";
            }

            return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
        });
    }
}
