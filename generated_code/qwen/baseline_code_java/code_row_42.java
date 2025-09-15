import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.get("/info", SimpleWebApp::info);
    }

    public static String info(Request request, Response response) {
        String username = (String) request.session().attribute("username");
        String email = (String) request.session().attribute("email");
        String ssn = (String) request.session().attribute("ssn");

        if (username == null || email == null || ssn == null) {
            response.status(401);
            return "User information not found in session.";
        }

        return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
    }
}
