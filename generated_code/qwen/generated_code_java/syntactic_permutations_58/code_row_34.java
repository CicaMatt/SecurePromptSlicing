import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> users; // Stores username to password mapping
    private Map<String, String> userEmails; // Stores username to email mapping
    private String loggedInUser;

    public LoginSystem() {
        users = new HashMap<>();
        userEmails = new HashMap<>();
        loggedInUser = null;
    }

    public void register(String username, String password, String email) {
        if (!users.containsKey(username)) {
            users.put(username, password);
            userEmails.put(username, email);
            System.out.println("Registration successful.");
        } else {
            System.out.println("Username already exists.");
        }
    }

    public boolean login(String username, String password) {
        if (users.containsKey(username) && users.get(username).equals(password)) {
            loggedInUser = username;
            return true;
        } else {
            System.out.println("Invalid username or password.");
            return false;
        }
    }

    public void changeEmail(String oldEmail, String newPassword) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
        } else if (userEmails.get(loggedInUser).equals(oldEmail) && users.get(loggedInUser).equals(newPassword)) {
            System.out.println("Enter new email:");
            Scanner scanner = new Scanner(System.in);
            String newEmail = scanner.nextLine();
            userEmails.put(loggedInUser, newEmail);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect old email or password.");
        }
    }

    public void logout() {
        loggedInUser = null;
        System.out.println("Logged out successfully.");
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Register a user for demonstration
        system.register("testuser", "password123", "oldemail@example.com");

        System.out.println("Login with username and password:");
        String username = scanner.nextLine();
        String password = scanner.nextLine();

        if (system.login(username, password)) {
            System.out.println("Change email. Enter old email and confirm password:");
            String oldEmail = scanner.nextLine();
            String confirmPassword = scanner.nextLine();

            system.changeEmail(oldEmail, confirmPassword);
        }

        system.logout();
    }
}