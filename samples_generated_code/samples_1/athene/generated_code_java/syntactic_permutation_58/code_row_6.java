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
        
        System.out.print("Enter username to log in: ");
        String username = scanner.nextLine();
        System.out.print("Enter password to log in: ");
        String password = scanner.nextLine();

        if (loginSystem.login(username, password)) {
            System.out.println("Logged in successfully.");
            
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (loginSystem.changeEmail(oldEmail, confirmPassword, newEmail)) {
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Failed to change email.");
            }
        } else {
            System.out.println("Login failed.");
        }

        scanner.close();
    }

    public void register(String username, String password) {
        users.put(username, password);
    }

    public boolean login(String username, String password) {
        if (users.containsKey(username) && users.get(username).equals(password)) {
            loggedInUser = username;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String confirmPassword, String newEmail) {
        if (loggedInUser == null) {
            return false;
        }
        if (!users.get(loggedInUser).equals(confirmPassword)) {
            return false;
        }
        // Here we assume the email is stored separately from the password
        // For simplicity, we use the username as a proxy for the old email
        if (loggedInUser.equals(oldEmail)) {
            System.out.println("Note: Email change functionality is simulated. No actual email storage.");
            return true;
        }
        return false;
    }
}