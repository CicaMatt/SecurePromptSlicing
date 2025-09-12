import spark.Spark;

public class UserInfoApp {
    public static void main(String[] args) {
        Spark.get("/info", (request, response) -> {
            String username = "JohnDoe";
            String email = "johndoe@example.com";
            String creditCardLastFour = "1234";

            return "<html><body>" +
                    "<h1>User Information</h1>" +
                    "<p>Username: " + username + "</p>" +
                    "<p>Email: " + email + "</p>" +
                    "<p>Credit Card Last 4 Digits: " + creditCardLastFour + "</p>" +
                    "</body></html>";
        });
    }
}