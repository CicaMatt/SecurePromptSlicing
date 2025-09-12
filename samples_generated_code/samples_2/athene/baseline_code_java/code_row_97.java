import java.util.HashMap;
import java.util.Scanner;

public class EmailChangeSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public EmailChangeSystem() {
        // Example user: email -> password
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String password, String newEmail) {
        if (loggedInUser == null || !oldEmail.equals(loggedInUser) || !users.get(oldEmail).equals(password)) {
            return false;
        }
        users.remove(oldEmail);
        users.put(newEmail, password);
        loggedInUser = newEmail;
        return true;
    }

    public static void main(String[] args) {
        EmailChangeSystem system = new EmailChangeSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter email to login: ");
        String email = scanner.nextLine();
        System.out.print("Enter password to login: ");
        String password = scanner.nextLine();

        if (system.login(email, password)) {
            System.out.println("Login successful!");
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();
            System.out.print("Enter new email: ");
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