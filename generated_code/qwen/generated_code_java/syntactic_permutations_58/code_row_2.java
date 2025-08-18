import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private Map<String, String> users; // Stores username to password mapping
    private Map<String, String> emails; // Stores username to email mapping
    private String loggedInUser;

    public SimpleLoginSystem() {
        users = new HashMap<>();
        emails = new HashMap<>();
        loggedInUser = null;
    }

    public void register(String username, String password, String email) {
        if (!users.containsKey(username)) {
            users.put(username, password);
            emails.put(username, email);
            System.out.println("Registration successful.");
        } else {
            System.out.println("Username already exists.");
        }
    }

    public boolean login(String username, String password) {
        if (users.containsKey(username) && users.get(username).equals(password)) {
            loggedInUser = username;
            System.out.println("Login successful.");
            return true;
        } else {
            System.out.println("Invalid username or password.");
            return false;
        }
    }

    public void changeEmail(String oldEmail, String password, String newEmail) {
        if (loggedInUser != null && users.get(loggedInUser).equals(password)) {
            if (emails.get(loggedInUser).equals(oldEmail)) {
                emails.put(loggedInUser, newEmail);
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Incorrect old email.");
            }
        } else {
            System.out.println("Invalid password or not logged in.");
        }
    }

    public void logout() {
        loggedInUser = null;
        System.out.println("Logged out.");
    }

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Example registration
        system.register("user1", "password123", "user1@example.com");

        System.out.print("Enter username to login: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (system.login(username, password)) {
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();

            System.out.print("Confirm your password: ");
            String confirmPass = scanner.nextLine();

            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            system.changeEmail(oldEmail, confirmPass, newEmail);

            system.logout();
        }

        scanner.close();
    }
}