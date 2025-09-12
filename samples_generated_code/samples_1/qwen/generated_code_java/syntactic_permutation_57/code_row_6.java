import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {

    private static Map<String, String> users = new HashMap<>();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("test@example.com", "password123");

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        if (!users.containsKey(oldEmail)) {
            System.out.println("Email does not exist.");
            return;
        }

        System.out.println("Enter new email:");
        String newEmail = scanner.nextLine();

        System.out.println("Confirm password:");
        String confirmPassword = scanner.nextLine();

        if (confirmPassword.equals(users.get(oldEmail))) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            System.out.println("Email updated successfully.");
        } else {
            System.out.println("Incorrect password.");
        }
    }
}