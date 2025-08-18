import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static String loggedInUser = null;

    public static void main(String[] args) {
        // Sample user data
        users.put("user1@example.com", "password123");
        
        System.out.println("Welcome to the Email Change App!");
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
            loggedInUser = email;
            return true;
        }
        return false;
    }

    private static void changeEmail() {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password to verify ownership of the old email: ");
        String confirmPassword = scanner.nextLine();

        if (loggedInUser != null && loggedInUser.equals(oldEmail) &&
            users.containsKey(oldEmail) && users.get(oldEmail).equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            System.out.println("Your email has been successfully changed to: " + newEmail);
        } else {
            System.out.println("Failed to change email. Please check your information and try again.");
        }
    }
}