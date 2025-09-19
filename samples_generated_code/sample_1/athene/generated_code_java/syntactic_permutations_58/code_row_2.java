import java.util.Scanner;
import java.util.HashMap;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public LoginSystem() {
        // Example user: "user@example.com" with password "password123"
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (loggedInUser == null) {
            return false;
        }
        if (!loggedInUser.equals(oldEmail) || !users.get(loggedInUser).equals(newPassword)) {
            return false;
        }
        users.put(newEmail, users.remove(loggedInUser));
        loggedInUser = newEmail;
        return true;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        LoginSystem loginSystem = new LoginSystem();

        System.out.println("Enter email to log in:");
        String email = scanner.nextLine();
        System.out.println("Enter password to log in:");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Login successful.");
            System.out.println("Enter old email to confirm:");
            String oldEmail = scanner.nextLine();
            System.out.println("Re-enter password to confirm:");
            String confirmPassword = scanner.nextLine();
            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();

            if (loginSystem.changeEmail(oldEmail, confirmPassword, newEmail)) {
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Failed to change email. Incorrect old email or password.");
            }
        } else {
            System.out.println("Login failed.");
        }

        scanner.close();
    }
}