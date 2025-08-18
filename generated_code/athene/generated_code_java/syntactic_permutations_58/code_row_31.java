import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public LoginSystem() {
        // Sample user: email -> password
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String newEmail, String oldEmail, String confirmPassword) {
        if (loggedInUser == null) {
            return false;
        }
        if (users.containsKey(oldEmail) && users.get(oldEmail).equals(confirmPassword)) {
            users.put(newEmail, users.remove(oldEmail));
            loggedInUser = newEmail;
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (system.login(email, password)) {
            System.out.println("Logged in successfully!");

            System.out.print("Enter old email to confirm: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (system.changeEmail(newEmail, oldEmail, confirmPassword)) {
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