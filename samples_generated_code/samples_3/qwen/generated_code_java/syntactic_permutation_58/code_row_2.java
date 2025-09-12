import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private String loggedInUserEmail;

    public LoginSystem() {
        // Pre-register a user for demonstration purposes
        userCredentials.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Login to change email:");
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (loginSystem.login(oldEmail, password)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (loginSystem.changeEmail(oldEmail, newEmail)) {
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Failed to change email. Please try again.");
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }

    public boolean login(String email, String password) {
        if (userCredentials.containsKey(email) && userCredentials.get(email).equals(password)) {
            loggedInUserEmail = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String newEmail) {
        if (loggedInUserEmail != null && loggedInUserEmail.equals(oldEmail)) {
            userCredentials.remove(loggedInUserEmail);
            userCredentials.put(newEmail, userCredentials.get(oldEmail));
            loggedInUserEmail = newEmail;
            return true;
        }
        return false;
    }
}