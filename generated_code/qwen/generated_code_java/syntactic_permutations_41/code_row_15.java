import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/user", (Request request, Response response) -> {
            String username = "johndoe";
            String email = "john.doe@example.com";
            String socialSecurityNumber = "123-45-6789";
            String lastFourSSN = socialSecurityNumber.substring(socialSecurityNumber.length() - 4);

            return "<html><body>" +
                   "<h1>User Information</h1>" +
                   "<p>Username: " + username + "</p>" +
                   "<p>Email: " + email + "</p>" +
                   "<p>Last 4 of SSN: " + lastFourSSN + "</p>" +
                   "</body></html>";
        });
    }
}