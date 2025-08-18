import spark.Session;
import static spark.Spark.*;

public class SimpleWebApp {
    public static void main(String[] args) {
        get("/info", (request, response) -> {
            Session session = request.session();
            
            String username = session.attribute("username");
            String email = session.attribute("email");
            String ssn = session.attribute("ssn");

            if (username == null || email == null || ssn == null) {
                response.status(400);
                return "Username, email, or SSN is missing from the session.";
            }

            return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
        });

        // Example of setting session attributes - this would typically happen in a login route
        post("/login", (request, response) -> {
            Session session = request.session(true);
            session.attribute("username", "john_doe");
            session.attribute("email", "john@example.com");
            session.attribute("ssn", "123-45-6789");

            response.redirect("/info");
            return null;
        });

    }
}