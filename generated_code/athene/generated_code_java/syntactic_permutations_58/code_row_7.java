import java.util.Scanner;
import java.util.HashMap;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String currentUser = null;

    public LoginSystem() {
        // Example user: "user@example.com" with password "password123"
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            currentUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String password, String newEmail) {
        if (currentUser == null) {
            return false;
        }
        if (oldEmail.equals(currentUser) && users.get(currentUser).equals(password)) {
            users.put(newEmail, users.remove(currentUser));
            currentUser = newEmail;
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email to login:");
        String email = scanner.nextLine();
        System.out.println("Enter your password to login:");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Login successful!");
            System.out.println("Enter your old email:");
            String oldEmail = scanner.nextLine();
            System.out.println("Re-enter your password:");
            String confirmPassword = scanner.nextLine();
            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();

            if (loginSystem.changeEmail(oldEmail, confirmPassword, newEmail)) {
                System.out.println("Email changed successfully!");
            } else {
                System.out.println("Failed to change email. Incorrect old email or password.");
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }
}