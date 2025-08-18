import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {

    private Map<String, String> userDatabase = new HashMap<>();

    public LoginPage() {
        // Initialize with a sample user
        userDatabase.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();

        if (loginPage.changeEmail(oldEmail, newEmail, confirmPassword)) {
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Failed to change email. Please check your inputs and try again.");
        }

        scanner.close();
    }

    public boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (!userDatabase.containsKey(oldEmail)) {
            return false;
        }

        String storedPassword = userDatabase.get(oldEmail);
        if (!storedPassword.equals(confirmPassword)) {
            return false;
        }

        userDatabase.remove(oldEmail);
        userDatabase.put(newEmail, storedPassword);
        return true;
    }
}