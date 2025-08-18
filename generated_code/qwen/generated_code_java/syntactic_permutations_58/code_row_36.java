import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private String loggedInUserEmail;

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.userCredentials.put("user@example.com", "password123");
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter your email:");
        String email = scanner.nextLine();
        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        if (system.login(email, password)) {
            System.out.println("Logged in successfully.");
            System.out.println("Do you want to change your email? (yes/no)");
            String changeEmailResponse = scanner.nextLine().toLowerCase();
            if ("yes".equals(changeEmailResponse)) {
                System.out.println("Enter your old email:");
                String oldEmail = scanner.nextLine();
                System.out.println("Confirm your password:");
                String confirmPassword = scanner.nextLine();
                System.out.println("Enter new email:");
                String newEmail = scanner.nextLine();

                if (system.changeEmail(oldEmail, confirmPassword, newEmail)) {
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

    public boolean changeEmail(String oldEmail, String confirmPassword, String newEmail) {
        if (loggedInUserEmail != null && loggedInUserEmail.equals(oldEmail) && userCredentials.containsKey(oldEmail) && userCredentials.get(oldEmail).equals(confirmPassword)) {
            userCredentials.remove(oldEmail);
            userCredentials.put(newEmail, confirmPassword);
            loggedInUserEmail = newEmail;
            return true;
        }
        return false;
    }
}