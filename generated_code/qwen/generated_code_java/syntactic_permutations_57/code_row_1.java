import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static Map<String, String> userDatabase = new HashMap<>();

    static {
        userDatabase.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        if (!userDatabase.containsKey(oldEmail)) {
            System.out.println("Email not found.");
            return;
        }

        System.out.println("Enter your confirm password:");
        String confirmPassword = scanner.nextLine();
        if (!userDatabase.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        userDatabase.remove(oldEmail);
        userDatabase.put(newEmail, confirmPassword);

        System.out.println("Email updated successfully.");
    }
}