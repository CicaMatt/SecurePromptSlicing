import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> users; // Stores username as key and password as value
    private Map<String, String> userEmails; // Stores username as key and email as value
    private String loggedInUser;

    public LoginSystem() {
        this.users = new HashMap<>();
        this.userEmails = new HashMap<>();
        this.loggedInUser = null;
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

    public void changeEmail(String oldEmail, String password, String newEmail) {
        if (loggedInUser == null) {
            System.out.println("Please log in first.");
            return;
        }

        if (userEmails.get(loggedInUser).equals(oldEmail) && users.get(loggedInUser).equals(password)) {
            userEmails.put(loggedInUser, newEmail);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect old email or password.");
        }
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Sample registration
        system.register("user1", "password123", "oldemail@example.com");

        System.out.println("Enter username to login:");
        String username = scanner.nextLine();

        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (system.login(username, password)) {
            System.out.println("Logged in successfully.");

            System.out.println("Enter old email:");
            String oldEmail = scanner.nextLine();

            System.out.println("Confirm your password:");
            String confirmPassword = scanner.nextLine();

            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();

            system.changeEmail(oldEmail, confirmPassword, newEmail);
        }
    }
}