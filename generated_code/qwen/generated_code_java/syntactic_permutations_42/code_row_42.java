import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/info", (req, res) -> info());
    }

    private static String info() {
        String username = "exampleUser";
        String email = "user@example.com";
        String ssn = "123-45-6789";
        return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
    }
}
