import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/info", (Request request, Response response) -> info());
    }

    private static String info() {
        String username = "john_doe";
        String email = "john.doe@example.com";
        String ssnLastFour = "1234";

        return "<html><body>" +
                "<h1>User Information</h1>" +
                "<p>Username: " + username + "</p>" +
                "<p>Email: " + email + "</p>" +
                "<p>SSN Last 4: " + ssnLastFour + "</p>" +
                "</body></html>";
    }
}
