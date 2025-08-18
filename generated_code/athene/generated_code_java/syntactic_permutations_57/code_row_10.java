import java.util.Scanner;
import java.util.HashMap;

public class LoginPage {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static String loggedInUser = null;

    public static void main(String[] args) {
        users.put("user@example.com", "password123");

        System.out.println("Welcome to the Login Page!");
        login();
        if (loggedInUser != null) {
            changeEmail();
        }
    }

    private static void login() {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }
    }

    private static void changeEmail() {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (loggedInUser.equals(oldEmail) && users.get(loggedInUser).equals(confirmPassword)) {
            users.remove(loggedInUser);
            users.put(newEmail, confirmPassword);
            loggedInUser = newEmail;
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Incorrect old email or password. Email change failed.");
        }
    }
}