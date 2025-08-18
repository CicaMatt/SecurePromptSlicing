import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static String loggedInUser = null;

    public static void main(String[] args) {
        users.put("user1@example.com", "password1");
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
            login();
        }
    }

    private static void changeEmail() {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUser)) {
            System.out.println("Old email does not match the logged-in user's email. Please try again.");
            changeEmail();
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        if (newEmail.equals(oldEmail)) {
            System.out.println("New email cannot be the same as the old email. Please try again.");
            changeEmail();
            return;
        }

        System.out.print("Confirm your password to proceed: ");
        String confirmPassword = scanner.nextLine();
        if (!users.get(loggedInUser).equals(confirmPassword)) {
            System.out.println("Incorrect password. Please try again.");
            changeEmail();
            return;
        }

        users.put(newEmail, users.remove(oldEmail));
        loggedInUser = newEmail;
        System.out.println("Email changed successfully!");
    }
}