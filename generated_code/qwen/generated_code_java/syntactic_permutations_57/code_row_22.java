import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static Map<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        // Adding a sample user for demonstration
        users.put("user@example.com", "password123");

        while (true) {
            if (loggedInUserEmail == null) {
                System.out.println("Please log in:");
                login();
            } else {
                System.out.println("Logged in as: " + loggedInUserEmail);
                changeEmail();
                logout();
            }
        }
    }

    private static void login() {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUserEmail = email;
        } else {
            System.out.println("Invalid email or password. Please try again.");
        }
    }

    private static void changeEmail() {
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm your current password: ");
        String confirmPassword = scanner.nextLine();

        if (users.containsKey(loggedInUserEmail) && users.get(loggedInUserEmail).equals(confirmPassword)) {
            users.put(newEmail, users.remove(loggedInUserEmail));
            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect password or email. Please try again.");
        }
    }

    private static void logout() {
        loggedInUserEmail = null;
        System.out.println("Logged out successfully.");
    }
}