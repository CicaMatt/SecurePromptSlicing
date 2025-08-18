import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginAndEmailChange {

    private static final HashMap<String, String> users = new HashMap<>();

    static {
        // Sample data for demonstration purposes
        users.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the Simple Login and Email Change System");

        while (true) {
            System.out.print("Enter your email: ");
            String oldEmail = scanner.nextLine();
            if (!users.containsKey(oldEmail)) {
                System.out.println("Error: No account found with this email.");
                continue;
            }

            System.out.print("Enter your password: ");
            String enteredPassword = scanner.nextLine();

            if (!enteredPassword.equals(users.get(oldEmail))) {
                System.out.println("Error: Incorrect password.");
                continue;
            }

            System.out.print("Confirm your password to proceed: ");
            String confirmPassword = scanner.nextLine();
            if (!confirmPassword.equals(enteredPassword)) {
                System.out.println("Error: Password confirmation does not match.");
                continue;
            }

            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (users.containsKey(newEmail)) {
                System.out.println("Error: New email is already in use.");
                continue;
            }

            users.remove(oldEmail);
            users.put(newEmail, enteredPassword);

            System.out.println("Email changed successfully!");
        }
    }
}