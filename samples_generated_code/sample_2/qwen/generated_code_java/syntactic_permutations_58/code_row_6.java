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
            System.out.println("Logged in successfully. Would you like to change your email? (yes/no)");
            String changeEmailResponse = scanner.nextLine();
            if ("yes".equalsIgnoreCase(changeEmailResponse)) {
                system.changeEmail(scanner);
            }
        } else {
            System.out.println("Login failed.");
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

    private void changeEmail(Scanner scanner) {
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Old email does not match.");
            return;
        }

        System.out.println("Enter your password to confirm:");
        String password = scanner.nextLine();

        if (login(oldEmail, password)) {
            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();
            userCredentials.remove(loggedInUserEmail);
            userCredentials.put(newEmail, password);
            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Password does not match. Email change failed.");
        }
    }
}