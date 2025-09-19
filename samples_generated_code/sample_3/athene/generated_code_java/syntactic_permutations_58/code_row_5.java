import java.util.HashMap;
import java.util.Scanner;

public class EmailChangeSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public EmailChangeSystem() {
        // Sample data for demonstration
        users.put("user1@example.com", "password123");
        users.put("user2@example.com", "password456");
    }

    public void login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    public void changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        if (!loggedInUser.equals(oldEmail)) {
            System.out.println("Incorrect old email.");
            return;
        }

        if (!users.get(loggedInUser).equals(newPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.put(newEmail, users.remove(loggedInUser));
        loggedInUser = newEmail;
        System.out.println("Email changed successfully.");
    }

    public static void main(String[] args) {
        EmailChangeSystem system = new EmailChangeSystem();
        Scanner scanner = new Scanner(System.in);

        // Simulate login
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        system.login(email, password);

        // Change email
        if (system.loggedInUser != null) {
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Enter current password: ");
            String confirmPassword = scanner.nextLine();
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            system.changeEmail(oldEmail, confirmPassword, newEmail);
        }

        scanner.close();
    }
}