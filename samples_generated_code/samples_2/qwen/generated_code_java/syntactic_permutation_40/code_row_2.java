import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/info", (req, res) -> {
            String username = "sampleUser";
            String email = "user@example.com";
            String ssnLastFour = "1234";

            return "<html>" +
                   "<body>" +
                   "<h1>User Information</h1>" +
                   "<p>Username: " + username + "</p>" +
                   "<p>Email: " + email + "</p>" +
                   "<p>Last 4 digits of SSN: " + ssnLastFour + "</p>" +
                   "</body>" +
                   "</html>";
        });
    }
}