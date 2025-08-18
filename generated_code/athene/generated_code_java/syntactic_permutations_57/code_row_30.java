import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Initialize a sample user for demonstration
        users.put("user@example.com", "password123");

        System.out.println("Login to change your email:");
        if (login()) {
            changeEmail();
        } else {
            System.out.println("Login failed. Exiting...");
        }
    }

    private static boolean login() {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            return true;
        }
        return false;
    }

    private static void changeEmail() {
        System.out.print("Enter your old email to confirm: ");
        String oldEmail = scanner.nextLine();
        if (!users.containsKey(oldEmail)) {
            System.out.println("Old email does not match. Email change failed.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm password to proceed: ");
        String confirmPassword = scanner.nextLine();
        if (!users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password. Email change failed.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);

        System.out.println("Email successfully changed to " + newEmail);
    }
}