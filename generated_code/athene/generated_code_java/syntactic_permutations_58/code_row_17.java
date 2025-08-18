import java.util.HashMap;
import java.util.Scanner;

public class LogSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedUser = null;

    public LogSystem() {
        // Initialize some users for demonstration
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String password, String newEmail) {
        if (loggedUser == null) {
            return false;
        }
        if (!loggedUser.equals(oldEmail) || !users.get(loggedUser).equals(password)) {
            return false;
        }
        users.put(newEmail, users.remove(loggedUser));
        loggedUser = newEmail;
        return true;
    }

    public static void main(String[] args) {
        LogSystem logSystem = new LogSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your email to login: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password to login: ");
        String password = scanner.nextLine();

        if (logSystem.login(email, password)) {
            System.out.println("Login successful!");
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();

            if (logSystem.changeEmail(oldEmail, confirmPassword, newEmail)) {
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