import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class EmailChangeApp {
    private static final Map<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Simulate logged-in user
        users.put("user@example.com", "password123");
        loggedInUser = "user@example.com";

        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        
        if (!users.containsKey(oldEmail)) {
            System.out.println("Old email does not match the account email.");
            return;
        }
        
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        String currentPassword = users.get(oldEmail);
        if (!currentPassword.equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, currentPassword);
        loggedInUser = newEmail;

        System.out.println("Email successfully changed to: " + newEmail);
    }
}