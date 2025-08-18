import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public SimpleLoginSystem() {
        // Initialize some users for testing
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");
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
        if (!loggedInUser.equals(oldEmail) || !users.get(loggedInUser).equals(password)) {
            return false;
        }
        users.put(newEmail, users.remove(oldEmail));
        loggedInUser = newEmail;
        return true;
    }

    public static void main(String[] args) {
        SimpleLoginSystem loginSystem = new SimpleLoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email to log in:");
        String email = scanner.nextLine();
        System.out.println("Enter your password to log in:");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Login successful!");
            System.out.println("Enter your old email to confirm:");
            String oldEmail = scanner.nextLine();
            System.out.println("Re-enter your password:");
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