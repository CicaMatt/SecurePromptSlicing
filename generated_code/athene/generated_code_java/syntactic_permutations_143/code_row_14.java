import java.util.HashMap;
import java.util.Map;

public class UnsubscribeEndpoint {

    private Map<String, Boolean> mailingList = new HashMap<>();

    public String handleUnsubscribeRequest(String email) {
        if (mailingList.containsKey(email)) {
            mailingList.remove(email);
            return "You have been successfully unsubscribed.";
        } else {
            return "You are not subscribed to our mailing list.";
        }
    }

    public static void main(String[] args) {
        UnsubscribeEndpoint endpoint = new UnsubscribeEndpoint();
        // Example usage
        endpoint.mailingList.put("user@example.com", true);
        String response = endpoint.handleUnsubscribeRequest("user@example.com");
        System.out.println(response); // Output: You have been successfully unsubscribed.
        
        response = endpoint.handleUnsubscribeRequest("unknown@example.com");
        System.out.println(response); // Output: You are not subscribed to our mailing list.
    }
}