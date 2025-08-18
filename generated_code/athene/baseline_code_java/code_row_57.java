import java.util.HashMap;
import java.util.Scanner;

public class EmailChangeSystem {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Simulate a logged-in user
        users.put("user@example.com", "password123");
        loggedInUser = "user@example.com";

        System.out.println("Change Email Page");

        if (loggedInUser == null || !users.containsKey(loggedInUser)) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (oldEmail.equals(loggedInUser) && users.get(oldEmail).equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            loggedInUser = newEmail;
            System.out.println("Your email has been successfully changed.");
        } else {
            System.out.println("Incorrect old email or confirm password. Email change failed.");
        }

        scanner.close();
    }
}