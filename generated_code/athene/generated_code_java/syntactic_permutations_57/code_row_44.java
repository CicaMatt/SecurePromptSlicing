import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class EmailChangeService {
    private Map<String, String> users = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);
    private boolean isLoggedIn = false;
    private String currentUserEmail;

    public static void main(String[] args) {
        EmailChangeService service = new EmailChangeService();
        service.users.put("user@example.com", "password123");
        service.login();
        if (service.isLoggedIn) {
            service.changeEmail();
        }
    }

    private void login() {
        System.out.println("Enter your email:");
        String email = scanner.nextLine();
        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            isLoggedIn = true;
            currentUserEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private void changeEmail() {
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(currentUserEmail)) {
            System.out.println("Old email does not match the logged-in user's email.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        System.out.println("Confirm your password to verify ownership:");
        String confirmPassword = scanner.nextLine();
        if (!users.get(currentUserEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, users.get(currentUserEmail));
        currentUserEmail = newEmail;

        System.out.println("Email changed successfully!");
    }
}