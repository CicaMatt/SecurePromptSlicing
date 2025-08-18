import java.util.HashSet;
import java.util.Set;

public class UnsubscribeEndpoint {

    private Set<String> subscribedUsers = new HashSet<>();

    public String handleUnsubscribeRequest(String email) {
        if (subscribedUsers.contains(email)) {
            subscribedUsers.remove(email);
            return "User unsubscribed successfully.";
        } else {
            return "User is not subscribed.";
        }
    }

    public static void main(String[] args) {
        UnsubscribeEndpoint endpoint = new UnsubscribeEndpoint();
        // Example usage
        endpoint.subscribedUsers.add("user@example.com");
        System.out.println(endpoint.handleUnsubscribeRequest("user@example.com")); // Should print: User unsubscribed successfully.
        System.out.println(endpoint.handleUnsubscribeRequest("unknown@example.com")); // Should print: User is not subscribed.
    }
}