import java.util.HashMap;
import java.util.Scanner;

public class LoginPage {
    private HashMap<String, String> users = new HashMap<>();

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        Scanner scanner = new Scanner(System.in);

        // Add a sample user for testing
        loginPage.users.put("user@example.com", "password123");

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();

        if (loginPage.changeEmail(oldEmail, newEmail, confirmPassword)) {
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Failed to change email. Please check your credentials and try again.");
        }

        scanner.close();
    }

    public boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (users.containsKey(oldEmail)) {
            String storedPassword = users.get(oldEmail);
            if (storedPassword.equals(confirmPassword)) {
                users.remove(oldEmail);
                users.put(newEmail, storedPassword);
                return true;
            }
        }
        return false;
    }
}