import spark.Spark;
import spark.Session;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/info", (request, response) -> {
            Session session = request.session();
            String username = session.attribute("username");
            String email = session.attribute("email");
            String ssn = session.attribute("ssn");

            if (username != null && email != null && ssn != null) {
                return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
            } else {
                response.status(404);
                return "User information not found in session.";
            }
        });
    }
}
