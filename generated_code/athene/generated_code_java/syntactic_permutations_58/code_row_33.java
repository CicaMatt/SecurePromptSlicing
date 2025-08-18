import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public LoginSystem() {
        // Pre-populate some users for testing
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String password, String newEmail) {
        if (loggedInUser == null) {
            return false;
        }
        if (loggedInUser.equals(oldEmail) && users.get(loggedInUser).equals(password)) {
            users.remove(loggedInUser);
            users.put(newEmail, password);
            loggedInUser = newEmail;
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email to log in:");
        String email = scanner.nextLine();
        System.out.println("Enter your password to log in:");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Login successful!");
            System.out.println("Enter your old email to confirm:");
            String oldEmail = scanner.nextLine();
            System.out.println("Re-enter your password:");
            String confirmPassword = scanner.nextLine();
            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();

            if (loginSystem.changeEmail(oldEmail, confirmPassword, newEmail)) {
                System.out.println("Email changed successfully!");
            } else {
                System.out.println("Failed to change email. Incorrect old email or password.");
            }
        } else {
            System.out.println("Login failed. Invalid credentials.");
        }

        scanner.close();
    }
}