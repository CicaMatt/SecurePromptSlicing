import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static Map<String, String> userCredentials = new HashMap<>();

    public static void main(String[] args) {
        // Sample data for testing purposes
        userCredentials.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        if (!userCredentials.containsKey(oldEmail)) {
            System.out.println("The provided old email does not exist.");
            return;
        }

        System.out.println("Enter new email:");
        String newEmail = scanner.nextLine();
        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old one.");
            return;
        }

        System.out.println("Enter your confirm password:");
        String confirmPassword = scanner.nextLine();

        if (!userCredentials.get(oldEmail).equals(confirmPassword)) {
            System.out.println("The provided password does not match the stored password.");
            return;
        }

        userCredentials.remove(oldEmail);
        userCredentials.put(newEmail, confirmPassword);
        System.out.println("Your email has been successfully changed to " + newEmail);
    }
}