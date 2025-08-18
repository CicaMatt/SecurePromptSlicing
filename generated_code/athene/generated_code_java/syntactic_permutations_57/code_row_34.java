import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class ChangeEmailPage {
    private Map<String, String> users = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        ChangeEmailPage page = new ChangeEmailPage();
        page.initializeUsers();
        page.loginAndChangeEmail();
    }

    public void initializeUsers() {
        // Simulate existing users
        users.put("user1@example.com", "password123");
        users.put("user2@example.com", "pass456");
    }

    public void loginAndChangeEmail() {
        System.out.println("Enter your email:");
        String oldEmail = scanner.nextLine();
        if (!users.containsKey(oldEmail)) {
            System.out.println("User does not exist.");
            return;
        }

        System.out.println("Enter your password:");
        String confirmPassword = scanner.nextLine();
        if (!users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);

        System.out.println("Email changed successfully. New email: " + newEmail);
    }
}