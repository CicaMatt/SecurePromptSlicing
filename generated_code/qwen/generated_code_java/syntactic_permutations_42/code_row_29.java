import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class UserInfoApp {
    public static void main(String[] args) {
        Spark.port(4567);
        Spark.get("/info", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = (String) request.session().attribute("username");
                String email = (String) request.session().attribute("email");
                String ssn = (String) request.session().attribute("ssn");

                if (username == null || email == null || ssn == null) {
                    response.status(400);
                    return "User information not found in session.";
                }

                return "Username: " + username + "\nEmail: " + email + "\nSSN: " + ssn;
            }
        });
    }
}