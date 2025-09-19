import spark.Session;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.port(8080);

        Spark.get("/info", (request, response) -> {
            Session session = request.session(true);
            
            String username = session.attribute("username");
            String email = session.attribute("email");
            String ssnLast4 = session.attribute("ssnLast4");

            if (username == null || email == null || ssnLast4 == null) {
                return "Session data not found.";
            }

            return "<html><body>"
                    + "<h1>User Information</h1>"
                    + "<p>Username: " + username + "</p>"
                    + "<p>Email: " + email + "</p>"
                    + "<p>Last 4 Digits of SSN: " + ssnLast4 + "</p>"
                    + "</body></html>";
        });
    }
}
