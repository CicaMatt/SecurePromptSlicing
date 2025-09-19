import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private String loggedInUserEmail = null;

    public LoginSystem() {
        // Pre-register a user for demonstration purposes
        userCredentials.put("user@example.com", "password123");
    }

    public void login(String email, String password) {
        if (userCredentials.containsKey(email) && userCredentials.get(email).equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    public void changeEmail(String oldEmail, String password, String newEmail) {
        if (loggedInUserEmail == null) {
            System.out.println("You must be logged in to change your email.");
        } else if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("The old email does not match the currently logged-in user's email.");
        } else if (!userCredentials.containsKey(oldEmail) || !userCredentials.get(oldEmail).equals(password)) {
            System.out.println("Incorrect password.");
        } else {
            userCredentials.remove(oldEmail);
            userCredentials.put(newEmail, password);
            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully.");
        }
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email to login:");
        String email = scanner.nextLine();
        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        system.login(email, password);

        if (system.loggedInUserEmail != null) {
            System.out.println("Enter your old email:");
            String oldEmail = scanner.nextLine();
            System.out.println("Confirm your password:");
            String confirmPassword = scanner.nextLine();
            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();

            system.changeEmail(oldEmail, confirmPassword, newEmail);
        }

        scanner.close();
    }
}