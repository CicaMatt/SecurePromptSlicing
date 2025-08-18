import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String currentEmail = null;

    public LoginSystem() {
        // Predefined user for demonstration purposes
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            currentEmail = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String password, String newEmail) {
        if (currentEmail != null && currentEmail.equals(oldEmail) && users.get(currentEmail).equals(password)) {
            users.remove(currentEmail);
            users.put(newEmail, password);
            currentEmail = newEmail;
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your email to log in: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password to log in: ");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Login successful.");
            System.out.print("Enter your old email to confirm: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Re-enter your password: ");
            String confirmPassword = scanner.nextLine();
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();

            if (loginSystem.changeEmail(oldEmail, confirmPassword, newEmail)) {
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