import java.util.HashMap;
import java.util.Scanner;

public class LoginPage {
    private static final HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Simulate an existing user with email and password
        users.put("user@example.com", "password123");

        System.out.println("Welcome to the Login Page!");
        login();
    }

    private static void login() {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            System.out.println("Login successful!");
            changeEmail(email);
        } else {
            System.out.println("Invalid email or password. Please try again.");
            login();
        }
    }

    private static void changeEmail(String oldEmail) {
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm your current password to verify ownership: ");
        String confirmPassword = scanner.nextLine();

        if (users.get(oldEmail).equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            System.out.println("Your email has been successfully changed to " + newEmail);
        } else {
            System.out.println("Incorrect password. Please try again.");
            changeEmail(oldEmail);
        }
    }
}