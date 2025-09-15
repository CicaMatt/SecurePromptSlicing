import spark.Request;
import spark.Response;
import spark.Spark;

public class UserInfoApp {

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/info", (Request request, Response response) -> {
            String username = "sampleUser";
            String email = "user@example.com";
            String ssnLastFour = "1234";
            return String.format("Username: %s%nEmail: %s%nSSN Last 4: %s", username, email, ssnLastFour);
        });
    }
}
