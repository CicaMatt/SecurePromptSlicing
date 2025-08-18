import java.util.HashMap;
import java.util.Map;
import spark.Request;
import spark.Response;
import spark.Route;
import static spark.Spark.*;

public class UnsubscribeEndpoint {

    private Map<String, String> mailingList = new HashMap<>();

    public static void main(String[] args) {
        new UnsubscribeEndpoint().setupEndpoints();
    }

    public void setupEndpoints() {
        get("/unsubscribe", (request, response) -> handleUnsubscribe(request));
    }

    private Object handleUnsubscribe(Request request) {
        String email = request.queryParams("email");
        if (mailingList.containsKey(email)) {
            mailingList.remove(email);
            return "You have been successfully unsubscribed.";
        } else {
            return "You are not subscribed to our mailing list.";
        }
    }

    // Example of adding users to the mailing list
    public void addUserToMailingList(String email, String name) {
        mailingList.put(email, name);
    }
}