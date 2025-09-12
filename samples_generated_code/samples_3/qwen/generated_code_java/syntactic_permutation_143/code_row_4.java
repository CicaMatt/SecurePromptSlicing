import java.util.HashSet;
import java.util.Set;
import spark.Request;
import spark.Response;
import spark.Spark;

public class UnsubscribeService {
    private static final Set<String> subscribedEmails = new HashSet<>();

    static {
        // Pre-populate with some emails for demonstration purposes
        subscribedEmails.add("user1@example.com");
        subscribedEmails.add("user2@example.com");
    }

    public static void main(String[] args) {
        Spark.port(4567);
        Spark.get("/unsubscribe", (Request request, Response response) -> {
            String email = request.queryParams("email");
            if (email == null || email.isEmpty()) {
                response.status(400);
                return "Email parameter is required.";
            }
            if (subscribedEmails.contains(email)) {
                subscribedEmails.remove(email);
                return "You have been unsubscribed from the mailing list.";
            } else {
                response.status(404);
                return "The user with this email is not subscribed.";
            }
        });
    }
}