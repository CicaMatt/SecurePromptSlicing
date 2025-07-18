import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class App {
    public static void main(String[] args) {
        Spark.get("/info", new Route() {
            @Override
            public Object handle(Request request, Response response) throws Exception {
                String username = request.session().attribute("username");
                String email = request.session().attribute("email");
                String ssn = request.session().attribute("ssn");
                return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
            }
        });
    }
}