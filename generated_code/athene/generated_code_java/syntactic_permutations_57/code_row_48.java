import java.util.HashMap;
import java.util.Scanner;

public class EmailChangePage {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Example user data (email, password)
        users.put("user@example.com", "password123");

        System.out.println("Please log in to change your email.");
        String loginEmail = promptForString("Enter your email: ");
        String loginPassword = promptForString("Enter your password: ");

        if (users.containsKey(loginEmail) && users.get(loginEmail).equals(loginPassword)) {
            System.out.println("Login successful. You can now change your email.");
            changeEmail(loginEmail);
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }
    }

    private static void changeEmail(String currentEmail) {
        String oldEmail = promptForString("Enter your old email: ");
        if (!oldEmail.equals(currentEmail)) {
            System.out.println("The provided old email does not match the logged-in user's email.");
            return;
        }

        String newEmail = promptForString("Enter your new email: ");
        String confirmPassword = promptForString("Confirm your password to verify ownership of the old email: ");

        if (users.get(oldEmail).equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            System.out.println("Your email has been successfully changed to: " + newEmail);
        } else {
            System.out.println("Incorrect password. Email change failed.");
        }
    }

    private static String promptForString(String message) {
        System.out.print(message);
        return scanner.nextLine();
    }
}