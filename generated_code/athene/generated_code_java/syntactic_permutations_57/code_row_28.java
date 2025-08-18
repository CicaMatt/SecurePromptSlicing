import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static String loggedInUser = null;

    public static void main(String[] args) {
        // Sample user data (email, password)
        users.put("user@example.com", "password123");

        login();
        if (loggedInUser != null) {
            changeEmail();
        }
    }

    private static void login() {
        System.out.println("Please log in to continue.");
        while (true) {
            System.out.print("Enter your email: ");
            String email = scanner.nextLine();
            System.out.print("Enter your password: ");
            String password = scanner.nextLine();

            if (users.containsKey(email) && users.get(email).equals(password)) {
                loggedInUser = email;
                System.out.println("Login successful!");
                break;
            } else {
                System.out.println("Invalid credentials. Please try again.");
            }
        }
    }

    private static void changeEmail() {
        System.out.println("Change your email address.");
        while (true) {
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            if (!oldEmail.equals(loggedInUser)) {
                System.out.println("The old email does not match the logged-in user.");
                continue;
            }

            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();

            System.out.print("Confirm your password to verify ownership: ");
            String confirmPassword = scanner.nextLine();
            if (!users.get(loggedInUser).equals(confirmPassword)) {
                System.out.println("Incorrect password. Please try again.");
                continue;
            }

            users.put(newEmail, users.remove(oldEmail));
            loggedInUser = newEmail;
            System.out.println("Your email has been successfully changed to: " + newEmail);
            break;
        }
    }
}