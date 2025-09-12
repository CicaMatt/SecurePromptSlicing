import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String currentUser = null;

    public LoginSystem() {
        // Pre-populate with a user for testing
        users.put("example@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            currentUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String newEmail, String oldEmail, String password) {
        if (currentUser == null) {
            return false;
        }
        if (!oldEmail.equals(currentUser) || !users.get(currentUser).equals(password)) {
            return false;
        }
        users.put(newEmail, users.remove(currentUser));
        currentUser = newEmail;
        return true;
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
            String oldEmail = scanner.nextLine();
            System.out.println("Confirm password:");
            String confirmPassword = scanner.nextLine();

            if (loginSystem.changeEmail(newEmail, oldEmail, confirmPassword)) {
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