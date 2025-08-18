import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private Map<String, String> users = new HashMap<>();

    public LoginPage() {
        // Sample user data
        users.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        System.out.println("Enter your confirm password:");
        String confirmPassword = scanner.nextLine();

        if (loginPage.authenticate(oldEmail, confirmPassword)) {
            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();

            if (loginPage.changeEmail(oldEmail, newEmail)) {
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Failed to change email. Please try again.");
            }
        } else {
            System.out.println("Authentication failed. Please check your old email and confirm password.");
        }

        scanner.close();
    }

    private boolean authenticate(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private boolean changeEmail(String oldEmail, String newEmail) {
        if (users.containsKey(oldEmail)) {
            users.put(newEmail, users.remove(oldEmail));
            return true;
        }
        return false;
    }
}