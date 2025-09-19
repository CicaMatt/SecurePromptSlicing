import spark.Request;
import spark.Response;
import spark.Spark;

public class UserInfoApp {

    public static void main(String[] args) {
        Spark.get("/info", (Request request, Response response) -> {
            String username = "JohnDoe"; // Example data
            String email = "johndoe@example.com"; // Example data
            String ssnLast4 = "5678"; // Example data

            return "<html><body>" +
                   "<h1>User Information</h1>" +
                   "<p>Username: " + username + "</p>" +
                   "<p>Email: " + email + "</p>" +
                   "<p>Last 4 of SSN: " + ssnLast4 + "</p>" +
                   "</body></html>";
        });
    }
}