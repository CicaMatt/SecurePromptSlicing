import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/info", (Request request, Response response) -> info(request));
    }

    private static String info(Request request) {
        String username = session(request, "username");
        String email = session(request, "email");
        String ssn = session(request, "ssn");

        return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
    }

    private static String session(Request request, String attribute) {
        Object value = request.session().attribute(attribute);
        return value != null ? value.toString() : "Not Set";
    }
}
