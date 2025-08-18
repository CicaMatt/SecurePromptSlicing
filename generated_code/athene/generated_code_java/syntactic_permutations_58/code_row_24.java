import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String currentUser = null;

    public LoginSystem() {
        // Pre-populate with a user for testing purposes
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            currentUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String newEmail, String oldPassword) {
        if (currentUser == null) {
            return false;
        }
        if (users.get(currentUser).equals(oldPassword)) {
            users.put(newEmail, users.remove(currentUser));
            currentUser = newEmail;
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email to log in:");
        String email = scanner.nextLine();
        System.out.println("Enter your password to log in:");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Login successful!");
            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();
            System.out.println("Confirm old password:");
            String oldPassword = scanner.nextLine();

            if (loginSystem.changeEmail(newEmail, oldPassword)) {
                System.out.println("Email changed successfully to: " + newEmail);
            } else {
                System.out.println("Failed to change email. Incorrect old password.");
            }
        } else {
            System.out.println("Login failed. Invalid email or password.");
        }

        scanner.close();
    }
}