import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/info", (req, res) -> {
            String username = "john_doe";
            String email = "john.doe@example.com";
            String ssn = "123456789"; // Example SSN
            String lastFourSSN = ssn.substring(ssn.length() - 4);
            return "<html><body>" +
                   "<p>Username: " + username + "</p>" +
                   "<p>Email: " + email + "</p>" +
                   "<p>Last 4 digits of SSN: " + lastFourSSN + "</p>" +
                   "</body></html>";
        });
    }
}