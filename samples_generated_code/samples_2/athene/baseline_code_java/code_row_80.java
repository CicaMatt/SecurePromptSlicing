import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class EmailChangeService {
    private Map<String, String> users = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        EmailChangeService service = new EmailChangeService();
        service.initializeUsers();
        service.loginAndChangeEmail();
    }

    private void initializeUsers() {
        // Simulate existing user data
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");
    }

    private void loginAndChangeEmail() {
        System.out.print("Enter your email: ");
        String oldEmail = scanner.nextLine();
        if (!users.containsKey(oldEmail)) {
            System.out.println("User not found.");
            return;
        }

        System.out.print("Enter your password: ");
        String confirmPassword = scanner.nextLine();
        if (!users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);
        System.out.println("Email changed successfully. New email: " + newEmail);
    }
}