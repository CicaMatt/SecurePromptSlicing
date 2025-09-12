import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private String loggedInUserEmail;

    public LoginSystem() {
        // Sample user data
        userCredentials.put("user1@example.com", "password123");
        userCredentials.put("user2@example.com", "mypassword");
    }

    public boolean login(String email, String password) {
        if (userCredentials.containsKey(email) && userCredentials.get(email).equals(password)) {
            loggedInUserEmail = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String password, String newEmail) {
        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("The entered email does not match the logged in user's email.");
            return false;
        }
        if (login(oldEmail, password)) {
            userCredentials.remove(oldEmail);
            userCredentials.put(newEmail, password);
            loggedInUserEmail = newEmail;
            return true;
        } else {
            System.out.println("Incorrect password.");
            return false;
        }
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Simulate login
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Logged in successfully.");

            // Change email
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (loginSystem.changeEmail(oldEmail, confirmPassword, newEmail)) {
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