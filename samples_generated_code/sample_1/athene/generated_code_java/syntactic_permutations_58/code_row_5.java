import java.util.HashMap;
import java.util.Scanner;

public class EmailChangeSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public EmailChangeSystem() {
        // Predefined user for demonstration
        users.put("user@example.com", "password123");
    }

    public void login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            System.out.println("Logged in successfully.");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    public void changeEmail(String oldEmail, String oldPassword, String newEmail) {
        if (loggedInUser != null && loggedInUser.equals(oldEmail) && users.get(loggedInUser).equals(oldPassword)) {
            users.put(newEmail, users.remove(loggedInUser));
            loggedInUser = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Failed to change email. Please check your credentials.");
        }
    }

    public static void main(String[] args) {
        EmailChangeSystem system = new EmailChangeSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter email to log in: ");
        String loginEmail = scanner.nextLine();
        System.out.print("Enter password to log in: ");
        String loginPassword = scanner.nextLine();

        system.login(loginEmail, loginPassword);

        if (system.loggedInUser != null) {
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm your password: ");
            String oldPassword = scanner.nextLine();
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();

            system.changeEmail(oldEmail, oldPassword, newEmail);
        }

        scanner.close();
    }
}