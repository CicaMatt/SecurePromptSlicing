import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String currentUser = null;

    public LoginSystem() {
        // Example user: email -> password
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            currentUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String newEmail, String oldEmail, String password) {
        if (currentUser == null || !oldEmail.equals(currentUser) || !users.get(currentUser).equals(password)) {
            return false;
        }
        users.remove(currentUser);
        users.put(newEmail, password);
        currentUser = newEmail;
        return true;
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email to log in:");
        String email = scanner.nextLine();
        System.out.println("Enter your password to log in:");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Logged in successfully.");
            System.out.println("Enter your old email to confirm:");
            String oldEmail = scanner.nextLine();
            System.out.println("Re-enter your password:");
            String confirmPassword = scanner.nextLine();
            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();

            if (loginSystem.changeEmail(newEmail, oldEmail, confirmPassword)) {
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Failed to change email.");
            }
        } else {
            System.out.println("Login failed.");
        }

        scanner.close();
    }
}