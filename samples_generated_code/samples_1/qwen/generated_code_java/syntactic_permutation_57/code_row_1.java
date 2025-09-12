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
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!userDatabase.containsKey(oldEmail)) {
            System.out.println("Error: Old email does not exist.");
            return;
        }

        if (!userDatabase.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Error: Incorrect password.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        if (newEmail.equals(oldEmail)) {
            System.out.println("Error: New email must be different from the old email.");
            return;
        }

        userDatabase.remove(oldEmail);
        userDatabase.put(newEmail, confirmPassword);

        System.out.println("Email changed successfully.");
    }
}