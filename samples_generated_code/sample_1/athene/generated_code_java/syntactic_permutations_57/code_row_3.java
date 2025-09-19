import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeLoginPage {
    private static HashMap<String, String> users = new HashMap<>();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        initializeUsers();

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();
        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();

        if (changeEmail(oldEmail, newEmail, confirmPassword)) {
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Failed to change email. Please check your details and try again.");
        }

        scanner.close();
    }

    private static void initializeUsers() {
        users.put("user@example.com", "password123");
        // Add more users if needed
    }

    private static boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (users.containsKey(oldEmail) && users.get(oldEmail).equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            return true;
        }
        return false;
    }
}