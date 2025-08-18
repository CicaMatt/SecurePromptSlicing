import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private Map<String, String> users = new HashMap<>();

    public LoginPage() {
        // Sample user data
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    public boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (!users.containsKey(oldEmail)) {
            System.out.println("Old email does not exist.");
            return false;
        }
        if (!login(oldEmail, confirmPassword)) {
            System.out.println("Incorrect password.");
            return false;
        }
        users.put(newEmail, users.remove(oldEmail));
        System.out.println("Email changed successfully.");
        return true;
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Enter your password to confirm: ");
        String confirmPassword = scanner.nextLine();

        loginPage.changeEmail(oldEmail, newEmail, confirmPassword);

        scanner.close();
    }
}