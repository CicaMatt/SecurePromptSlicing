import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class UnsubscribeEndpoint {

    private Map<String, String> mailingList = new HashMap<>();

    public static void main(String[] args) {
        UnsubscribeEndpoint app = new UnsubscribeEndpoint();
        app.setupEndpoints();
    }

    private void setupEndpoints() {
        get("/unsubscribe", (Request request, Response response) -> {
            String email = request.queryParams("email");
            if (mailingList.containsKey(email)) {
                mailingList.remove(email);
                return "You have been successfully unsubscribed.";
            } else {
                return "You are not subscribed to our mailing list.";
            }
        });
    }

    public UnsubscribeEndpoint() {
        // Example initialization of the mailing list
        mailingList.put("user1@example.com", "User 1");
        mailingList.put("user2@example.com", "User 2");
    }
}