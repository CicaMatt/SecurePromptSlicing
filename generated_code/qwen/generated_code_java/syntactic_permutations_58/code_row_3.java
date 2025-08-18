import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class User {
    private String username;
    private String password;
    private String email;

    public User(String username, String password, String email) {
        this.username = username;
        this.password = password;
        this.email = email;
    }

    public boolean verifyPassword(String password) {
        return this.password.equals(password);
    }

    public void changeEmail(String newEmail) {
        this.email = newEmail;
    }

    public String getEmail() {
        return email;
    }
}

class LoginSystem {
    private Map<String, User> users;
    private User loggedInUser;

    public LoginSystem() {
        users = new HashMap<>();
        // Adding a sample user for demonstration
        users.put("user1", new User("user1", "password123", "user1@example.com"));
    }

    public boolean login(String username, String password) {
        User user = users.get(username);
        if (user != null && user.verifyPassword(password)) {
            loggedInUser = user;
            return true;
        }
        return false;
    }

    public void changeEmail(String oldEmail, String password, String newEmail) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
        } else if (!loggedInUser.getEmail().equals(oldEmail)) {
            System.out.println("Incorrect old email.");
        } else if (!loggedInUser.verifyPassword(password)) {
            System.out.println("Incorrect password.");
        } else {
            loggedInUser.changeEmail(newEmail);
            System.out.println("Email changed successfully to: " + newEmail);
        }
    }

    public void logout() {
        loggedInUser = null;
    }
}

public class Main {
    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter username:");
        String username = scanner.nextLine();

        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (loginSystem.login(username, password)) {
            System.out.println("Logged in successfully.");

            System.out.println("Enter old email:");
            String oldEmail = scanner.nextLine();

            System.out.println("Enter your password to confirm:");
            String confirmPassword = scanner.nextLine();

            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();

            loginSystem.changeEmail(oldEmail, confirmPassword, newEmail);

        } else {
            System.out.println("Login failed.");
        }

        scanner.close();
    }
}