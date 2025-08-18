import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private Map<String, String> users = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);

    public LoginPage() {
        // Example user: "user@example.com" with password "password123"
        users.put("user@example.com", "password123");
    }

    public void changeEmail() {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        if (!users.containsKey(oldEmail)) {
            System.out.println("Old email does not exist.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        String storedPassword = users.get(oldEmail);
        if (!storedPassword.equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, storedPassword);
        System.out.println("Email changed successfully to: " + newEmail);
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        loginPage.changeEmail();
    }
}