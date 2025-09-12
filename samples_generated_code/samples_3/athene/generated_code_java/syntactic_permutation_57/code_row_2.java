import java.util.Scanner;
import java.util.HashMap;

public class EmailChangePage {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static String loggedInUser = null;

    public static void main(String[] args) {
        users.put("user@example.com", "password123");
        login();
        changeEmail();
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
            login();
        }
    }

    private static void changeEmail() {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(loggedInUser)) {
            System.out.println("Old email does not match the logged-in user.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (!users.get(loggedInUser).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);
        loggedInUser = newEmail;

        System.out.println("Email changed successfully!");
    }
}