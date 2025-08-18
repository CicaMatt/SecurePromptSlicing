import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static final Map<String, String> userCredentials = new HashMap<>();
    private static final Map<String, String> userEmails = new HashMap<>();

    static {
        // Predefined user credentials for demonstration purposes
        userCredentials.put("user1", "password1");
        userEmails.put("user1", "user1@example.com");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter username:");
        String username = scanner.nextLine();

        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (authenticateUser(username, password)) {
            changeEmail(scanner, username);
        } else {
            System.out.println("Authentication failed. Please try again.");
        }

        scanner.close();
    }

    private static boolean authenticateUser(String username, String password) {
        return userCredentials.containsKey(username) && userCredentials.get(username).equals(password);
    }

    private static void changeEmail(Scanner scanner, String username) {
        System.out.println("Enter old email:");
        String oldEmail = scanner.nextLine();

        if (!userEmails.get(username).equals(oldEmail)) {
            System.out.println("The entered old email does not match the current email.");
            return;
        }

        System.out.println("Enter new email:");
        String newEmail = scanner.nextLine();

        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        System.out.println("Confirm password:");
        String confirmPassword = scanner.nextLine();

        if (!userCredentials.get(username).equals(confirmPassword)) {
            System.out.println("Incorrect password. Please try again.");
            return;
        }

        userEmails.put(username, newEmail);
        System.out.println("Email successfully updated to: " + newEmail);
    }
}