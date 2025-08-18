import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {

    private static Map<String, String> userDatabase = new HashMap<>();

    public static void main(String[] args) {
        // Example user in the database
        userDatabase.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        if (!userDatabase.containsKey(oldEmail)) {
            System.out.println("Error: Old email does not exist.");
            return;
        }

        System.out.println("Enter your confirm password:");
        String confirmPassword = scanner.nextLine();

        if (!userDatabase.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Error: Incorrect password.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        if (newEmail.equals(oldEmail)) {
            System.out.println("Error: New email is the same as old email.");
            return;
        }

        userDatabase.remove(oldEmail);
        userDatabase.put(newEmail, confirmPassword);

        System.out.println("Email changed successfully!");
    }
}