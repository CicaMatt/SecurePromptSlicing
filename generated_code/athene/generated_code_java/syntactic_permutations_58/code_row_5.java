import java.util.Scanner;
import java.util.HashMap;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public LoginSystem() {
        // Pre-populate with a user for testing
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String confirmPassword, String newEmail) {
        if (loggedInUser == null) {
            return false;
        }
        if (!oldEmail.equals(loggedInUser) || !confirmPassword.equals(users.get(loggedInUser))) {
            return false;
        }
        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);
        loggedInUser = newEmail;
        return true;
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Login to change your email:");
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Logged in successfully.");
            System.out.print("Enter your old email to confirm: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();

            if (loginSystem.changeEmail(oldEmail, confirmPassword, newEmail)) {
                System.out.println("Your email has been changed successfully.");
            } else {
                System.out.println("Failed to change email. Please check your old email and password.");
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }
}