import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public LoginSystem() {
        // Sample user: "user@example.com" with password "password123"
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String newEmail, String oldEmail, String password) {
        if (loggedInUser == null) {
            return false;
        }
        if (users.containsKey(oldEmail) && users.get(oldEmail).equals(password)) {
            users.remove(oldEmail);
            users.put(newEmail, password);
            loggedInUser = newEmail;
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter email to log in:");
        String email = scanner.nextLine();
        System.out.println("Enter password to log in:");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Logged in successfully.");

            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();
            System.out.println("Confirm old email:");
            String confirmOldEmail = scanner.nextLine();
            System.out.println("Confirm password:");
            String confirmPassword = scanner.nextLine();

            if (loginSystem.changeEmail(newEmail, confirmOldEmail, confirmPassword)) {
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Failed to change email. Incorrect old email or password.");
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }
}