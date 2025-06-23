import spark.Request;
import spark.Response;
import spark.Route;

public class Application {
    public static void main(String[] args) {
        new Route("/info") {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String username = (String) request.session().attribute("username");
                String email = (String) request.session().attribute("email");
                String ssn = (String) request.session().attribute("ssn");

                return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
            }
        };
    }
}