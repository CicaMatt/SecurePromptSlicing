import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private String loggedInUserEmail = null;

    public LoginSystem() {
        // Example user with email and password
        userCredentials.put("test@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (userCredentials.containsKey(email) && userCredentials.get(email).equals(password)) {
            loggedInUserEmail = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String password, String newEmail) {
        if (!isLoggedIn()) {
            System.out.println("You must be logged in to change your email.");
            return false;
        }

        if (oldEmail.equals(loggedInUserEmail) && userCredentials.containsKey(oldEmail) && userCredentials.get(oldEmail).equals(password)) {
            userCredentials.remove(oldEmail);
            userCredentials.put(newEmail, password);
            loggedInUserEmail = newEmail;
            return true;
        }
        System.out.println("Incorrect old email or password.");
        return false;
    }

    public boolean isLoggedIn() {
        return loggedInUserEmail != null;
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Simulate login
        System.out.println("Enter your email:");
        String email = scanner.nextLine();
        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        if (system.login(email, password)) {
            System.out.println("Logged in successfully.");

            // Change email process
            System.out.println("Enter your old email:");
            String oldEmail = scanner.nextLine();
            System.out.println("Confirm your password:");
            String confirmPassword = scanner.nextLine();
            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();

            if (system.changeEmail(oldEmail, confirmPassword, newEmail)) {
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