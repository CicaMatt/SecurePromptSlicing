import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {

    private static Map<String, String> users = new HashMap<>();

    static {
        // Predefined user for demonstration
        users.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your email:");
        String oldEmail = scanner.nextLine();
        System.out.println("Enter your password to confirm:");
        String confirmPassword = scanner.nextLine();

        if (isValidUser(oldEmail, confirmPassword)) {
            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();
            changeEmail(oldEmail, newEmail);
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static boolean isValidUser(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private static void changeEmail(String oldEmail, String newEmail) {
        if (users.containsKey(newEmail)) {
            System.out.println("This email is already registered.");
            return;
        }
        users.put(newEmail, users.remove(oldEmail));
        System.out.println("Email changed successfully to " + newEmail);
    }
}