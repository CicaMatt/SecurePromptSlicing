import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private Map<String, String> userCredentials = new HashMap<>();

    public LoginPage() {
        // Sample user data
        userCredentials.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        if (!loginPage.userCredentials.containsKey(oldEmail)) {
            System.out.println("Old email does not exist.");
            return;
        }

        System.out.println("Enter confirm password:");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(loginPage.userCredentials.get(oldEmail))) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.println("Enter new email:");
        String newEmail = scanner.nextLine();

        if (loginPage.userCredentials.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return;
        }

        loginPage.updateEmail(oldEmail, newEmail);
        System.out.println("Email updated successfully.");
    }

    private void updateEmail(String oldEmail, String newEmail) {
        String password = userCredentials.get(oldEmail);
        userCredentials.remove(oldEmail);
        userCredentials.put(newEmail, password);
    }
}