import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String currentEmail = null;

    public LoginSystem() {
        // Predefined user: email -> password
        users.put("user@example.com", "password123");
    }

    public void login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            currentEmail = email;
            System.out.println("Logged in successfully.");
        } else {
            System.out.println("Login failed.");
        }
    }

    public void changeEmail() {
        if (currentEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (oldEmail.equals(currentEmail) && users.get(currentEmail).equals(confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            users.put(newEmail, users.remove(currentEmail));
            currentEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter email to log in: ");
        String email = scanner.nextLine();
        System.out.print("Enter password to log in: ");
        String password = scanner.nextLine();

        loginSystem.login(email, password);

        if (loginSystem.currentEmail != null) {
            loginSystem.changeEmail();
        }
    }
}