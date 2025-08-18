import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginPage {

    private static final HashMap<String, String> users = new HashMap<>();

    public static void main(String[] args) {
        // Initial setup of a user for demonstration purposes
        users.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the Login Page!");

        while (true) {
            System.out.print("Enter email: ");
            String oldEmail = scanner.nextLine();
            if (!users.containsKey(oldEmail)) {
                System.out.println("No account found with that email. Please try again.");
                continue;
            }

            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            if (!password.equals(users.get(oldEmail))) {
                System.out.println("Incorrect password. Please try again.");
                continue;
            }

            // User is authenticated
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();

            if (!password.equals(confirmPassword)) {
                System.out.println("Passwords do not match. Please try again.");
                continue;
            }

            if (users.containsKey(newEmail) && !newEmail.equals(oldEmail)) {
                System.out.println("New email is already in use. Please choose a different one.");
                continue;
            }

            // Update the user's email
            users.remove(oldEmail);
            users.put(newEmail, password);

            System.out.println("Email changed successfully to: " + newEmail);
        }
    }
}