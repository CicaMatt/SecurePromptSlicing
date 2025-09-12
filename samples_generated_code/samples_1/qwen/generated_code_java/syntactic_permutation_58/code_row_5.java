import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> users = new HashMap<>();
    private String loggedInUserEmail;

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.users.put("user@example.com", "password123"); // Sample user
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email:");
        String email = scanner.nextLine();

        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        if (system.login(email, password)) {
            System.out.println("Logged in successfully. Would you like to change your email? (yes/no)");
            String changeEmailResponse = scanner.nextLine();
            if (changeEmailResponse.equalsIgnoreCase("yes")) {
                system.changeEmail(scanner);
            }
        } else {
            System.out.println("Invalid email or password.");
        }

        scanner.close();
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUserEmail = email;
            return true;
        }
        return false;
    }

    public void changeEmail(Scanner scanner) {
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        System.out.println("Confirm your password:");
        String password = scanner.nextLine();

        if (loggedInUserEmail.equals(oldEmail) && users.containsKey(oldEmail) && users.get(oldEmail).equals(password)) {
            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();
            users.remove(loggedInUserEmail);
            users.put(newEmail, password);
            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Failed to change email. Incorrect old email or password.");
        }
    }
}