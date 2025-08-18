import java.util.Scanner;
import java.util.HashMap;

public class EmailChangePage {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Simulate user login
        System.out.println("Enter your email to log in:");
        String loginEmail = scanner.nextLine();
        System.out.println("Enter your password to log in:");
        String loginPassword = scanner.nextLine();
        
        if (users.containsKey(loginEmail) && users.get(loginEmail).equals(loginPassword)) {
            loggedInUser = loginEmail;
            changeEmail(scanner);
        } else {
            System.out.println("Login failed. Please try again.");
        }
        
        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("You are not logged in.");
            return;
        }

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(loggedInUser)) {
            System.out.println("Incorrect old email.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        System.out.println("Confirm your password to change the email:");
        String confirmPassword = scanner.nextLine();

        if (users.get(loggedInUser).equals(confirmPassword)) {
            users.remove(loggedInUser);
            users.put(newEmail, confirmPassword);
            loggedInUser = newEmail;
            System.out.println("Your email has been successfully changed to: " + newEmail);
        } else {
            System.out.println("Incorrect password.");
        }
    }

    static {
        // Pre-populate some users for testing
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");
    }
}