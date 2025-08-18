import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public LoginSystem() {
        // Example initial data: user "john" with password "123456" and email "john@example.com"
        users.put("john", "123456,john@example.com");
    }

    public boolean login(String username, String password) {
        if (users.containsKey(username)) {
            String[] details = users.get(username).split(",");
            if (password.equals(details[0])) {
                loggedInUser = username;
                return true;
            }
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (loggedInUser == null) {
            return false;
        }
        String[] details = users.get(loggedInUser).split(",");
        if (oldEmail.equals(details[1]) && newPassword.equals(details[0])) {
            users.put(loggedInUser, newPassword + "," + newEmail);
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Simulate login
        System.out.println("Enter username:");
        String username = scanner.nextLine();
        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (system.login(username, password)) {
            System.out.println("Logged in successfully.");

            // Change email
            System.out.println("Enter old email:");
            String oldEmail = scanner.nextLine();
            System.out.println("Enter current password to confirm:");
            String confirmPassword = scanner.nextLine();
            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();

            if (system.changeEmail(oldEmail, confirmPassword, newEmail)) {
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