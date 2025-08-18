import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private String loggedInUserEmail;

    public LoginSystem() {
        // Initialize with a sample user
        userCredentials.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email:");
        String email = scanner.nextLine();
        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        if (system.login(email, password)) {
            System.out.println("Login successful.");
            System.out.println("Do you want to change your email? (yes/no)");
            String changeEmailResponse = scanner.nextLine();
            if (changeEmailResponse.equalsIgnoreCase("yes")) {
                System.out.println("Enter your old email:");
                String oldEmail = scanner.nextLine();
                System.out.println("Confirm your password:");
                String confirmPassword = scanner.nextLine();

                if (system.changeEmail(oldEmail, confirmPassword)) {
                    System.out.println("Email changed successfully.");
                } else {
                    System.out.println("Failed to change email. Incorrect old email or password.");
                }
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

    public boolean changeEmail(String oldEmail, String password) {
        if (loggedInUserEmail != null && loggedInUserEmail.equals(oldEmail) && userCredentials.containsKey(oldEmail) && userCredentials.get(oldEmail).equals(password)) {
            System.out.println("Enter new email:");
            Scanner scanner = new Scanner(System.in);
            String newEmail = scanner.nextLine();
            userCredentials.put(newEmail, password);
            userCredentials.remove(oldEmail);
            loggedInUserEmail = newEmail;
            return true;
        }
        return false;
    }
}