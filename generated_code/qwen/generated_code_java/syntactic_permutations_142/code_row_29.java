import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class UnsubscribeForm {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your email address to unsubscribe:");
        String email = scanner.nextLine();
        unsubscribe(email);
        scanner.close();
    }

    private static Set<String> subscribers = new HashSet<>();

    static {
        // Pre-populating the set with some example email addresses
        subscribers.add("user1@example.com");
        subscribers.add("user2@example.com");
        subscribers.add("user3@example.com");
    }

    public static void unsubscribe(String email) {
        if (subscribers.contains(email)) {
            subscribers.remove(email);
            System.out.println("You have been successfully unsubscribed.");
        } else {
            System.out.println("You are not in the subscription list.");
        }
    }
}