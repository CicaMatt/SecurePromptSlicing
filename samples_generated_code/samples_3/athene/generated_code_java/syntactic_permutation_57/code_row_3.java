import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static String loggedInUser = null;

    public static void main(String[] args) {
        users.put("user1@example.com", "password123");
        login();
        changeEmail();
    }

    private static void login() {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            System.out.println("Logged in successfully.");
        } else {
            System.out.println("Invalid credentials.");
            System.exit(0);
        }
    }

    private static void changeEmail() {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!oldEmail.equals(loggedInUser) || !users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect old email or confirm password.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        while (users.containsKey(newEmail)) {
            System.out.println("This email is already in use. Please enter a different email:");
            newEmail = scanner.nextLine();
        }

        users.put(newEmail, users.remove(oldEmail));
        loggedInUser = newEmail;
        System.out.println("Email changed successfully to: " + newEmail);
    }
}