import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private Map<String, String> userDatabase = new HashMap<>();

    public LoginPage() {
        // Sample user data
        userDatabase.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        if (!loginPage.userDatabase.containsKey(oldEmail)) {
            System.out.println("Old email does not exist.");
            return;
        }

        System.out.println("Enter your confirm password:");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(loginPage.userDatabase.get(oldEmail))) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        if (loginPage.userDatabase.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return;
        }

        loginPage.changeEmail(oldEmail, newEmail);
        System.out.println("Email changed successfully.");
    }

    private void changeEmail(String oldEmail, String newEmail) {
        String password = userDatabase.remove(oldEmail);
        userDatabase.put(newEmail, password);
    }
}