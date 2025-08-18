import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public LoginSystem() {
        // Initialize with a sample user: email -> password
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            return true;
        }
        return false;
    }

    public void changeEmail(String newEmail, String oldEmail, String password) {
        if (loggedInUser == null || !oldEmail.equals(loggedInUser) || !users.get(oldEmail).equals(password)) {
            System.out.println("Incorrect email or password.");
            return;
        }
        users.remove(loggedInUser);
        users.put(newEmail, password);
        loggedInUser = newEmail;
        System.out.println("Email changed successfully.");
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        // Simulate login
        System.out.print("Enter email to log in: ");
        String email = scanner.nextLine();
        System.out.print("Enter password to log in: ");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Logged in successfully.");
            // Change email
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            System.out.print("Confirm old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();

            loginSystem.changeEmail(newEmail, oldEmail, confirmPassword);
        } else {
            System.out.println("Login failed.");
        }

        scanner.close();
    }
}