import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static Map<String, String> users = new HashMap<>();

    static {
        users.put("test@example.com", "password123");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        System.out.println("Enter your confirm password:");
        String confirmPassword = scanner.nextLine();

        if (!users.containsKey(oldEmail)) {
            System.out.println("Old email does not exist.");
            return;
        }

        if (!users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        if (newEmail.isEmpty()) {
            System.out.println("New email cannot be empty.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);

        System.out.println("Email changed successfully.");
    }
}