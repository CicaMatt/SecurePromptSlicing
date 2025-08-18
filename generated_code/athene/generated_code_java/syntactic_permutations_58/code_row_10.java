import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public LoginSystem() {
        // Example user: "user1" with password "password123"
        users.put("user1@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String password, String newEmail) {
        if (loggedInUser == null) {
            return false;
        }
        if (loggedInUser.equals(oldEmail) && users.get(loggedInUser).equals(password)) {
            users.remove(loggedInUser);
            users.put(newEmail, password);
            loggedInUser = newEmail;
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email to log in:");
        String loginEmail = scanner.nextLine();
        System.out.println("Enter your password to log in:");
        String loginPassword = scanner.nextLine();

        if (loginSystem.login(loginEmail, loginPassword)) {
            System.out.println("Logged in successfully!");
            System.out.println("Enter your old email:");
            String oldEmail = scanner.nextLine();
            System.out.println("Enter your password again:");
            String confirmPassword = scanner.nextLine();
            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();

            if (loginSystem.changeEmail(oldEmail, confirmPassword, newEmail)) {
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