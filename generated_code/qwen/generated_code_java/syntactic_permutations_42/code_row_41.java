import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/info", (Request request, Response response) -> info());
    }

    private static String info() {
        String username = "exampleUser";
        String email = "user@example.com";
        String ssn = "123-45-6789";
        return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
    }
}
