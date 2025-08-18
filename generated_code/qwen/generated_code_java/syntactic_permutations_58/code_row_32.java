import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private String loggedInUser = null;

    public LoginSystem() {
        // Adding a sample user for demonstration purposes
        userCredentials.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (userCredentials.containsKey(email) && userCredentials.get(email).equals(password)) {
            loggedInUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String newEmail, String password) {
        if (!isLoggedIn()) {
            System.out.println("You must be logged in to change your email.");
            return false;
        }

        if (oldEmail.equals(loggedInUser) && userCredentials.containsKey(oldEmail) && userCredentials.get(oldEmail).equals(password)) {
            userCredentials.remove(oldEmail);
            userCredentials.put(newEmail, password);
            loggedInUser = newEmail;
            return true;
        }
        return false;
    }

    public boolean isLoggedIn() {
        return loggedInUser != null;
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your email to log in: ");
        String email = scanner.nextLine();

        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Login successful!");

            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();

            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();

            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();

            if (loginSystem.changeEmail(oldEmail, newEmail, confirmPassword)) {
                System.out.println("Email changed successfully!");
            } else {
                System.out.println("Failed to change email. Please check your old email and password.");
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }
}