import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public LoginSystem() {
        // Sample data for demonstration purposes
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String newEmail, String oldEmail, String confirmPassword) {
        if (loggedInUser == null) {
            return false;
        }
        if (!oldEmail.equals(loggedInUser) || !users.get(loggedInUser).equals(confirmPassword)) {
            return false;
        }
        users.put(newEmail, users.remove(loggedInUser));
        loggedInUser = newEmail;
        return true;
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter email to login:");
        String email = scanner.nextLine();
        System.out.println("Enter password to login:");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Login successful. You can now change your email.");
            System.out.println("Enter old email for confirmation:");
            String oldEmail = scanner.nextLine();
            System.out.println("Confirm your password:");
            String confirmPassword = scanner.nextLine();
            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();

            if (loginSystem.changeEmail(newEmail, oldEmail, confirmPassword)) {
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Failed to change email. Incorrect old email or password.");
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }
}