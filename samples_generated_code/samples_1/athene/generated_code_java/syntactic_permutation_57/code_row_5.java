import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private Map<String, String> users = new HashMap<>();
    private Map<String, String> emails = new HashMap<>();
    private String currentUser;

    public LoginPage() {
        // Example user data
        users.put("user1", "password1");
        emails.put("user1", "user1@example.com");
    }

    public boolean login(String username, String password) {
        if (users.containsKey(username) && users.get(username).equals(password)) {
            currentUser = username;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (currentUser == null) {
            return false;
        }
        String currentPassword = users.get(currentUser);
        String currentEmail = emails.get(currentUser);

        if (currentEmail.equals(oldEmail) && currentPassword.equals(confirmPassword)) {
            emails.put(currentUser, newEmail);
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (loginPage.login(username, password)) {
            System.out.println("Login successful.");

            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();

            if (loginPage.changeEmail(oldEmail, newEmail, confirmPassword)) {
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Failed to change email. Please check your details and try again.");
            }
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }
}