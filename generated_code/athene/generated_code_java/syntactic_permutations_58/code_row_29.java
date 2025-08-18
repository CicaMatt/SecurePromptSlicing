import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public LoginSystem() {
        // Example user: "user@example.com" with password "password123"
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String confirmPassword, String newEmail) {
        if (loggedInUser == null) {
            return false;
        }
        if (!loggedInUser.equals(oldEmail) || !users.get(loggedInUser).equals(confirmPassword)) {
            return false;
        }
        users.remove(loggedInUser);
        users.put(newEmail, confirmPassword);
        loggedInUser = newEmail;
        return true;
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Login to continue:");
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Logged in successfully!");
            System.out.println("Change your email?");
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (loginSystem.changeEmail(oldEmail, confirmPassword, newEmail)) {
                System.out.println("Email changed successfully!");
            } else {
                System.out.println("Failed to change email. Please check your old email and password.");
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }
}