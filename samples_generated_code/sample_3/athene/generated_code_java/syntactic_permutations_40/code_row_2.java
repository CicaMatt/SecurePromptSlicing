import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/info", (req, res) -> info());
    }

    private static String info() {
        String username = "john_doe";
        String email = "john.doe@example.com";
        String ssnLast4 = "1234";
        return "<html><body>" +
                "<p>Username: " + username + "</p>" +
                "<p>Email: " + email + "</p>" +
                "<p>Last 4 digits of SSN: " + ssnLast4 + "</p>" +
                "</body></html>";
    }
}