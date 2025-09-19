import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private Map<String, String> users; // Stores username as key and password as value
    private Map<String, String> emails; // Stores username as key and email as value
    private String loggedInUser;

    public SimpleLoginSystem() {
        users = new HashMap<>();
        emails = new HashMap<>();
        loggedInUser = null;
        // Adding a default user for demonstration
        addUser("user", "password123");
        setEmail("user", "user@example.com");
    }

    public void addUser(String username, String password) {
        users.put(username, password);
    }

    public void setEmail(String username, String email) {
        emails.put(username, email);
    }

    public boolean login(String username, String password) {
        if (users.containsKey(username) && users.get(username).equals(password)) {
            loggedInUser = username;
            return true;
        }
        return false;
    }

    public void changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (!isLoggedIn()) {
            System.out.println("You must be logged in to change your email.");
            return;
        }
        if (emails.get(loggedInUser).equals(oldEmail) && users.get(loggedInUser).equals(newPassword)) {
            setEmail(loggedInUser, newEmail);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Failed to change email. Incorrect old email or password.");
        }
    }

    public boolean isLoggedIn() {
        return loggedInUser != null;
    }

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter username to login:");
        String username = scanner.nextLine();

        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (system.login(username, password)) {
            System.out.println("Logged in successfully.");

            System.out.println("Enter your old email:");
            String oldEmail = scanner.nextLine();

            System.out.println("Confirm your password:");
            String confirmPassword = scanner.nextLine();

            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();

            system.changeEmail(oldEmail, confirmPassword, newEmail);
        } else {
            System.out.println("Login failed.");
        }

        scanner.close();
    }
}