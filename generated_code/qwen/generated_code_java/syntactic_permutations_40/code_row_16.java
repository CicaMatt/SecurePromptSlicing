import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/info", SimpleWebApp::info);
    }

    private static String info(Request request, Response response) {
        String username = (String) request.session().attribute("username");
        String email = (String) request.session().attribute("email");
        String ssn = (String) request.session().attribute("ssn");

        if (username == null || email == null || ssn == null) {
            response.status(401);
            return "Session data not found.";
        }

        String lastFourSSN = ssn.substring(ssn.length() - 4);

        return "<html><body>" +
                "<h1>User Information</h1>" +
                "<p>Username: " + username + "</p>" +
                "<p>Email: " + email + "</p>" +
                "<p>Last 4 digits of SSN: " + lastFourSSN + "</p>" +
                "</body></html>";
    }
}