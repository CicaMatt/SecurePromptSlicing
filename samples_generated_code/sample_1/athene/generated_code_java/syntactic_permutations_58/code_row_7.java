import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Simulate a registered user
        loginSystem.register("user1", "password123");
        loginSystem.login(scanner, "user1", "password123");

        if (loginSystem.isLoggedIn()) {
            System.out.println("Enter your old email:");
            String oldEmail = scanner.nextLine();
            System.out.println("Confirm your password:");
            String confirmPassword = scanner.nextLine();
            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();

            if (loginSystem.changeEmail(oldEmail, confirmPassword, newEmail)) {
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Failed to change email.");
            }
        }

        scanner.close();
    }

    public void register(String username, String password) {
        users.put(username + ":" + generateDefaultEmail(username), password);
    }

    private String generateDefaultEmail(String username) {
        return username + "@example.com";
    }

    public boolean login(Scanner scanner, String username, String password) {
        if (users.containsKey(username + ":" + generateDefaultEmail(username)) && users.get(username + ":" + generateDefaultEmail(username)).equals(password)) {
            loggedInUser = username;
            return true;
        }
        return false;
    }

    public boolean isLoggedIn() {
        return loggedInUser != null;
    }

    public boolean changeEmail(String oldEmail, String confirmPassword, String newEmail) {
        if (isLoggedIn()) {
            String key = loggedInUser + ":" + oldEmail;
            if (users.containsKey(key) && users.get(key).equals(confirmPassword)) {
                users.remove(key);
                users.put(loggedInUser + ":" + newEmail, confirmPassword);
                return true;
            }
        }
        return false;
    }
}