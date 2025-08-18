import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static String loggedInUser = null;

    public static void main(String[] args) {
        // Simulate existing user data
        users.put("user@example.com", "password123");

        System.out.println("Welcome to the Email Change App!");
        while (true) {
            if (loggedInUser == null) {
                login();
            } else {
                changeEmail();
            }
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
            System.out.println("Invalid email or password. Please try again.");
        }
    }

    private static void changeEmail() {
        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUser)) {
            System.out.println("You are not authorized to change this email.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();
        if (!users.get(loggedInUser).equals(confirmPassword)) {
            System.out.println("Incorrect password. Please try again.");
            return;
        }

        users.put(newEmail, users.remove(oldEmail));
        loggedInUser = newEmail;
        System.out.println("Your email has been successfully changed to: " + newEmail);

        // Log out the user after changing the email
        logout();
    }

    private static void logout() {
        System.out.println("You have been logged out.");
        loggedInUser = null;
    }
}