import java.util.Scanner;
import java.util.HashMap;

public class LoginSystem {
    private HashMap<String, String> userCredentials = new HashMap<>();
    private String loggedInUserEmail;

    public LoginSystem() {
        // Pre-populate with a test user
        userCredentials.put("user@example.com", "password123");
        loggedInUserEmail = null;
    }

    public boolean login(String email, String password) {
        if (userCredentials.containsKey(email) && userCredentials.get(email).equals(password)) {
            loggedInUserEmail = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String password, String newEmail) {
        if (isLoggedIn() && loggedInUserEmail.equals(oldEmail) && userCredentials.containsKey(oldEmail) && userCredentials.get(oldEmail).equals(password)) {
            userCredentials.remove(oldEmail);
            userCredentials.put(newEmail, password);
            loggedInUserEmail = newEmail;
            return true;
        }
        return false;
    }

    public boolean isLoggedIn() {
        return loggedInUserEmail != null;
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Login to change email");
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (system.login(oldEmail, password)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (system.changeEmail(oldEmail, password, newEmail)) {
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Failed to change email. Please check your old email and password.");
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }
}