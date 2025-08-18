import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private String loggedInUser = null;

    public LoginSystem() {
        // Initialize with a sample user
        userCredentials.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (userCredentials.containsKey(email) && userCredentials.get(email).equals(password)) {
            loggedInUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String password, String newEmail) {
        if (isLoggedIn() && loggedInUser.equals(oldEmail) && userCredentials.containsKey(oldEmail) && userCredentials.get(oldEmail).equals(password)) {
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
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email to log in:");
        String loginEmail = scanner.nextLine();
        System.out.println("Enter your password:");
        String loginPassword = scanner.nextLine();

        if (system.login(loginEmail, loginPassword)) {
            System.out.println("Login successful!");
            System.out.println("Do you want to change your email? (yes/no)");
            String changeEmailResponse = scanner.nextLine();

            if ("yes".equalsIgnoreCase(changeEmailResponse)) {
                System.out.println("Enter your old email:");
                String oldEmail = scanner.nextLine();
                System.out.println("Confirm your password:");
                String confirmPassword = scanner.nextLine();
                System.out.println("Enter your new email:");
                String newEmail = scanner.nextLine();

                if (system.changeEmail(oldEmail, confirmPassword, newEmail)) {
                    System.out.println("Email changed successfully!");
                } else {
                    System.out.println("Failed to change email. Please check your old email and password.");
                }
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }
}