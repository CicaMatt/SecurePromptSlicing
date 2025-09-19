import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String currentEmail = null;

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Register a user
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        loginSystem.registerUser(username, email, password);

        // Log in the user
        System.out.print("Enter your email to log in: ");
        String loginEmail = scanner.nextLine();
        System.out.print("Enter your password to log in: ");
        String loginPassword = scanner.nextLine();
        if (loginSystem.login(loginEmail, loginPassword)) {
            System.out.println("Login successful!");
        } else {
            System.out.println("Login failed.");
            return;
        }

        // Change email
        System.out.print("Enter old email to confirm: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter password to confirm: ");
        String confirmPassword = scanner.nextLine();
        if (loginSystem.changeEmail(oldEmail, confirmPassword)) {
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Failed to change email.");
        }
    }

    public void registerUser(String username, String email, String password) {
        users.put(email, password);
        currentEmail = email;
        System.out.println("User registered with email: " + email);
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            currentEmail = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String confirmPassword) {
        if (currentEmail == null || !currentEmail.equals(oldEmail) || !users.get(currentEmail).equals(confirmPassword)) {
            return false;
        }
        System.out.print("Enter new email: ");
        Scanner scanner = new Scanner(System.in);
        String newEmail = scanner.nextLine();
        users.put(newEmail, users.remove(currentEmail));
        currentEmail = newEmail;
        return true;
    }
}