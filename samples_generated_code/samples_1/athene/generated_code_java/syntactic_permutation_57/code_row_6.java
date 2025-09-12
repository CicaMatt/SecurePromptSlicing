import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static String loggedInUser;

    public static void main(String[] args) {
        users.put("user@example.com", "password123");
        
        System.out.println("Welcome to the Email Change App!");
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
            System.out.println("Invalid credentials.");
        }
    }

    private static void changeEmail() {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (!loggedInUser.equals(oldEmail)) {
            System.out.println("Old email does not match the logged-in user.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm your password to verify ownership: ");
        String confirmPassword = scanner.nextLine();
        if (!users.get(loggedInUser).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);
        loggedInUser = newEmail;

        System.out.println("Your email has been successfully changed to: " + newEmail);
    }
}