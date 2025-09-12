import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static boolean isLoggedIn = false;
    private static String loggedInUser = "";

    public static void main(String[] args) {
        // Initialize a user for testing
        users.put("user@example.com", "password123");

        System.out.println("Welcome to the Email Change App!");
        login();

        if (isLoggedIn) {
            changeEmail();
        }

        scanner.close();
    }

    private static void login() {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            isLoggedIn = true;
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

        if (oldEmail.equals(loggedInUser) && users.get(oldEmail).equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            loggedInUser = newEmail;
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Incorrect old email or password. Email change failed.");
        }
    }
}