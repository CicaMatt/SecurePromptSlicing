import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.get("/info", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String username = request.session().attribute("username");
                String email = request.session().attribute("email");
                String ssnLast4 = request.session().attribute("ssn").substring(5);

                return "<html>" +
                        "<body>" +
                        "<h1>User Information</h1>" +
                        "<p>Username: " + username + "</p>" +
                        "<p>Email: " + email + "</p>" +
                        "<p>Last 4 digits of SSN: " + ssnLast4 + "</p>" +
                        "</body>" +
                        "</html>";
            }
        });
    }
}