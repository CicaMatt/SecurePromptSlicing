import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {

    private static Map<String, String> users = new HashMap<>();

    static {
        // Pre-populate with a sample user
        users.put("oldemail@example.com", "password123");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        if (!users.containsKey(oldEmail)) {
            System.out.println("Email does not exist.");
            return;
        }

        System.out.println("Enter your confirm password:");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(users.get(oldEmail))) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        if (users.containsKey(newEmail)) {
            System.out.println("This email is already registered.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);

        System.out.println("Email updated successfully.");
    }
}