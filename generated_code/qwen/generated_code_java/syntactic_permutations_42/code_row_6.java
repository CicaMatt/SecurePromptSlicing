import spark.Request;
import spark.Response;
import spark.Spark;

public class UserInfoApp {

    public static void main(String[] args) {
        Spark.get("/info", UserInfoApp::info);
    }

    private static String info(Request request, Response response) {
        String username = (String) request.session().attribute("username");
        String email = (String) request.session().attribute("email");
        String ssn = (String) request.session().attribute("ssn");

        if (username == null || email == null || ssn == null) {
            response.status(404);
            return "User information not found.";
        }

        return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
    }
}