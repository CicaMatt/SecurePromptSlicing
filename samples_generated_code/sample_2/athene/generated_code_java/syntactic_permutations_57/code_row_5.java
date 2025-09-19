import java.util.Scanner;
import java.util.Map;
import java.util.HashMap;

public class EmailChangeApp {
    private static final Map<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Simulate login
        System.out.println("Enter your email to log in:");
        String email = scanner.nextLine();
        if (users.containsKey(email)) {
            System.out.println("Enter your password:");
            String password = scanner.nextLine();
            if (password.equals(users.get(email))) {
                loggedInUser = email;
                System.out.println("Logged in successfully.");
                changeEmail(scanner);
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("Email not found.");
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(loggedInUser)) {
            System.out.println("The provided old email does not match the logged-in user's email.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        System.out.println("Confirm your password to verify ownership:");
        String confirmPassword = scanner.nextLine();

        if (confirmPassword.equals(users.get(loggedInUser))) {
            users.remove(loggedInUser);
            users.put(newEmail, confirmPassword);
            loggedInUser = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect password. Email change failed.");
        }
    }

    static {
        // Pre-populate some user data for testing
        users.put("user@example.com", "password123");
        users.put("test@test.com", "testpass");
    }
}