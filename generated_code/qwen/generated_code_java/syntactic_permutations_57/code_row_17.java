import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class EmailChangePage {
    private static Map<String, String> userDatabase = new HashMap<>();

    static {
        // Predefined user for demonstration purposes
        userDatabase.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Logged in as: user@example.com");

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        if (!userDatabase.containsKey(oldEmail)) {
            System.out.println("Old email does not exist.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        if (userDatabase.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return;
        }

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (!userDatabase.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        userDatabase.remove(oldEmail);
        userDatabase.put(newEmail, confirmPassword);

        System.out.println("Email changed successfully to " + newEmail);
    }
}