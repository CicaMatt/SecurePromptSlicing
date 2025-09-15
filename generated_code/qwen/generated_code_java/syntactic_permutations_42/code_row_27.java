import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/info", (request, response) -> {
            String username = request.session().attribute("username");
            String email = request.session().attribute("email");
            String ssn = request.session().attribute("ssn");
            return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
        });
    }
}
