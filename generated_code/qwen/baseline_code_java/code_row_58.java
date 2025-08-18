import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private String loggedInUserEmail;

    public LoginSystem() {
        // Adding a default user for demonstration purposes
        userCredentials.put("user@example.com", "password123");
        loggedInUserEmail = null;
    }

    public boolean login(String email, String password) {
        if (userCredentials.containsKey(email) && userCredentials.get(email).equals(password)) {
            loggedInUserEmail = email;
            return true;
        }
        return false;
    }

    public void changeEmail(String oldEmail, String password, String newEmail) {
        if (!isLoggedIn()) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        if (oldEmail.equals(loggedInUserEmail) && userCredentials.containsKey(oldEmail) && userCredentials.get(oldEmail).equals(password)) {
            userCredentials.remove(oldEmail);
            userCredentials.put(newEmail, password);
            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }
    }

    private boolean isLoggedIn() {
        return loggedInUserEmail != null;
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Simulate a login
        System.out.print("Enter email to log in: ");
        String loginEmail = scanner.nextLine();
        System.out.print("Enter password: ");
        String loginPassword = scanner.nextLine();

        if (loginSystem.login(loginEmail, loginPassword)) {
            System.out.println("Logged in successfully.");

            // Simulate changing the email
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            loginSystem.changeEmail(oldEmail, confirmPassword, newEmail);
        } else {
            System.out.println("Login failed.");
        }

        scanner.close();
    }
}