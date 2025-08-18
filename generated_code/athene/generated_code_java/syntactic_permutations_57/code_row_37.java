import java.util.HashMap;
import java.util.Scanner;

public class EmailChangeApp {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        // Simulate login for a user
        System.out.println("Enter your email to log in:");
        String userEmail = scanner.nextLine();
        if (users.containsKey(userEmail)) {
            loggedInUser = userEmail;
            System.out.println("Logged in as " + loggedInUser);
            changeEmail(scanner);
        } else {
            System.out.println("No account found with that email.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUser)) {
            System.out.println("You are not logged in as the user for this email.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        System.out.println("Confirm your password to verify ownership:");
        String confirmPassword = scanner.nextLine();
        if (users.get(oldEmail).equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            loggedInUser = newEmail;
            System.out.println("Your email has been successfully changed to: " + newEmail);
        } else {
            System.out.println("Incorrect password. Email change failed.");
        }
    }

    static {
        // Pre-populate some user data for testing
        users.put("user@example.com", "password123");
        users.put("john.doe@example.com", "letmein");
    }
}