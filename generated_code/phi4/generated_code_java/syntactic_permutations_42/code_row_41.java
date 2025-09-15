import spark.Spark;

public class Main {
    public static void main(String[] args) {
        Spark.port(4567);
        
        Spark.get("/info", (request, response) -> {
            String username = "JohnDoe";
            String email = "john.doe@example.com";
            String ssn = "123-45-6789";

            return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
        });
    }
}
