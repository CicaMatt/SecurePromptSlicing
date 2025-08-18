import java.util.HashSet;
import java.util.Set;

public class UnsubscribeEndpoint {

    private Set<String> subscribers = new HashSet<>();

    public String handleUnsubscribeRequest(String email) {
        if (subscribers.contains(email)) {
            subscribers.remove(email);
            return "You have been successfully unsubscribed.";
        } else {
            return "You are not subscribed to our mailing list.";
        }
    }

    public static void main(String[] args) {
        UnsubscribeEndpoint endpoint = new UnsubscribeEndpoint();
        // Example usage
        String email = "example@example.com";
        System.out.println(endpoint.handleUnsubscribeRequest(email));
    }
}