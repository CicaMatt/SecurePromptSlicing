import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static Map<String, String> users = new HashMap<>();
    private static String loggedInEmail = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user@example.com", "password123");

        System.out.println("Welcome to the Simple Login System!");

        while (true) {
            if (loggedInEmail == null) {
                System.out.println("\nPlease log in:");
                System.out.print("Enter your email: ");
                String email = scanner.nextLine();
                System.out.print("Enter your password: ");
                String password = scanner.nextLine();

                if (login(email, password)) {
                    loggedInEmail = email;
                    System.out.println("Login successful!");
                } else {
                    System.out.println("Invalid email or password.");
                }
            } else {
                System.out.println("\nYou are logged in as " + loggedInEmail);
                System.out.print("Do you want to change your email? (yes/no): ");
                String response = scanner.nextLine();

                if ("yes".equalsIgnoreCase(response)) {
                    System.out.print("Enter your old email: ");
                    String oldEmail = scanner.nextLine();
                    System.out.print("Confirm your password: ");
                    String password = scanner.nextLine();
                    System.out.print("Enter your new email: ");
                    String newEmail = scanner.nextLine();

                    if (changeEmail(oldEmail, password, newEmail)) {
                        loggedInEmail = newEmail;
                        System.out.println("Email changed successfully!");
                    } else {
                        System.out.println("Failed to change email. Incorrect old email or password.");
                    }
                }

                System.out.print("Do you want to log out? (yes/no): ");
                String logoutResponse = scanner.nextLine();
                if ("yes".equalsIgnoreCase(logoutResponse)) {
                    loggedInEmail = null;
                    System.out.println("You have been logged out.");
                }
            }
        }
    }

    private static boolean login(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private static boolean changeEmail(String oldEmail, String password, String newEmail) {
        if (users.containsKey(oldEmail) && users.get(oldEmail).equals(password)) {
            users.remove(oldEmail);
            users.put(newEmail, password);
            return true;
        }
        return false;
    }
}