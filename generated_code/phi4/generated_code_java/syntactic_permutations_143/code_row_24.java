import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class UnsubscribeService {

    private Map<String, Boolean> subscribers = new HashMap<>();

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        
        // Sample data
        service.subscribers.put("test@example.com", true);
        service.subscribers.put("user@example.com", true);

        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter email to unsubscribe:");
        String email = scanner.nextLine();

        String result = service.unsubscribe(email);
        System.out.println(result);
    }

    public String unsubscribe(String email) {
        if (subscribers.containsKey(email)) {
            subscribers.remove(email); // Unsubscribe the user
            return "User unsubscribed successfully.";
        } else {
            return "The user is not subscribed.";
        }
    }
}