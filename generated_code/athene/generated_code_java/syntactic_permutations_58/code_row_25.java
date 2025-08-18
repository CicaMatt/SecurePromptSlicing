import java.util.Scanner;
import java.util.HashMap;

public class SimpleLoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public SimpleLoginSystem() {
        // Predefined user for testing
        users.put("user@example.com", "password123");
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
        if (users.containsKey(oldEmail) && users.get(oldEmail).equals(password)) {
            users.put(newEmail, users.remove(oldEmail));
            loggedInUser = newEmail;
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        SimpleLoginSystem loginSystem = new SimpleLoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter email to log in: ");
        String email = scanner.nextLine();
        System.out.print("Enter password to log in: ");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            System.out.println("Logged in successfully.");
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Re-enter password: ");
            String rePassword = scanner.nextLine();
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (loginSystem.changeEmail(oldEmail, rePassword, newEmail)) {
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Failed to change email. Incorrect old email or password.");
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }
}