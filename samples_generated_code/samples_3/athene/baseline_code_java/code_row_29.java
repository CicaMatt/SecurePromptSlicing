import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedUser = null;

    public LoginSystem() {
        // Sample user data (email, password)
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String newEmail, String oldEmail, String password) {
        if (loggedUser == null) return false;

        if (loggedUser.equals(oldEmail) && users.get(loggedUser).equals(password)) {
            users.put(newEmail, users.remove(loggedUser));
            loggedUser = newEmail;
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your email to login: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password to login: ");
        String password = scanner.nextLine();

        if (system.login(email, password)) {
            System.out.println("Login successful!");
            System.out.print("Enter your old email to confirm: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Re-enter your password to confirm: ");
            String confirmPassword = scanner.nextLine();
            System.out.print("Enter your new email: ");
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