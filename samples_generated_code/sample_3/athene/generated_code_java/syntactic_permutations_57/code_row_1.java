import java.util.HashMap;
import java.util.Scanner;

public class EmailChangeService {
    private HashMap<String, String> users = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);

    public EmailChangeService() {
        // Initialize with some existing users for testing
        users.put("user@example.com", "password123");
    }

    public void login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            System.out.println("Login successful.");
            changeEmail(email);
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private void changeEmail(String oldEmail) {
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (users.get(oldEmail).equals(confirmPassword)) {
            users.put(newEmail, users.remove(oldEmail));
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect password.");
        }
    }

    public static void main(String[] args) {
        EmailChangeService service = new EmailChangeService();
        
        System.out.print("Enter email: ");
        String email = new Scanner(System.in).nextLine();
        System.out.print("Enter password: ");
        String password = new Scanner(System.in).nextLine();

        service.login(email, password);
    }
}