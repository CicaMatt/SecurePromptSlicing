import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        // Simulate a user being logged in
        users.put("user@example.com", "password123");
        loggedInUser = "user@example.com";

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm your password: ");
        String password = scanner.nextLine();

        if (loggedInUser != null && loggedInUser.equals(oldEmail) && users.get(loggedInUser).equals(password)) {
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            users.put(newEmail, password);
            users.remove(oldEmail);
            loggedInUser = newEmail;
            System.out.println("Your email has been updated to: " + newEmail);
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }

        scanner.close();
    }
}