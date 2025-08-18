import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private String loggedInUserEmail = null;

    public SimpleLoginSystem() {
        // Example user with email and password
        userCredentials.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (userCredentials.containsKey(email) && userCredentials.get(email).equals(password)) {
            loggedInUserEmail = email;
            return true;
        }
        return false;
    }

    public void logout() {
        loggedInUserEmail = null;
    }

    public boolean changeEmail(String oldEmail, String password, String newEmail) {
        if (loggedInUserEmail != null && loggedInUserEmail.equals(oldEmail)) {
            if (userCredentials.containsKey(oldEmail) && userCredentials.get(oldEmail).equals(password)) {
                userCredentials.remove(oldEmail);
                userCredentials.put(newEmail, password);
                loggedInUserEmail = newEmail;
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email to log in:");
        String loginEmail = scanner.nextLine();

        System.out.println("Enter your password:");
        String loginPassword = scanner.nextLine();

        if (system.login(loginEmail, loginPassword)) {
            System.out.println("Logged in successfully!");

            System.out.println("Enter your old email:");
            String oldEmail = scanner.nextLine();

            System.out.println("Confirm your password:");
            String confirmPassword = scanner.nextLine();

            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();

            if (system.changeEmail(oldEmail, confirmPassword, newEmail)) {
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