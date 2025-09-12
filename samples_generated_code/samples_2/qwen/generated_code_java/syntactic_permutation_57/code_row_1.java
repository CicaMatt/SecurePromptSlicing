import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static Map<String, String> users = new HashMap<>();

    static {
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
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static boolean isValidUser(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private static void changeEmail(String oldEmail, String newEmail) {
        String password = users.remove(oldEmail);
        users.put(newEmail, password);
    }
}