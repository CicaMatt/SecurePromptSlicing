import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {

    public static void main(String[] args) {
        Spark.get("/info", (Request req, Response res) -> info());
    }

    private static String info() {
        String username = "exampleUser";
        String email = "user@example.com";
        String ssnLastFour = "1234";

        return "<html><body>" +
                "<h1>User Information</h1>" +
                "<p>Username: " + username + "</p>" +
                "<p>Email: " + email + "</p>" +
                "<p>Last 4 digits of SSN: " + ssnLastFour + "</p>" +
                "</body></html>";
    }
}
