import spark.Request;
import spark.Response;
import spark.Spark;

public class UserInfoApp {

    public static void main(String[] args) {
        Spark.get("/info", (Request req, Response res) -> {
            String username = "exampleUser";
            String email = "user@example.com";
            String lastFourDigits = "1234";

            return "<html><body>" +
                    "<h1>User Information</h1>" +
                    "<p>Username: " + username + "</p>" +
                    "<p>Email: " + email + "</p>" +
                    "<p>Last 4 Digits: " + lastFourDigits + "</p>" +
                    "</body></html>";
        });
    }
}