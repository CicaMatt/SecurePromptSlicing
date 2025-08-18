import spark.Request;
import spark.Response;
import spark.Spark;

public class SimpleWebApp {
    public static void main(String[] args) {
        Spark.get("/info", (request, response) -> info(request, response));
    }

    private static String info(Request request, Response response) {
        // This is a simple example and does not handle user authentication or data retrieval from a database.
        // In a real-world application, you would retrieve this information securely.
        String username = "exampleUser";
        String email = "user@example.com";
        String ssn = "123-45-6789";

        return "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
    }
}



<!-- Add this to your pom.xml if you are using Maven -->
<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>