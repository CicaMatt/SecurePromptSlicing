import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static Map<String, String> userCredentials = new HashMap<>();

    static {
        userCredentials.put("example@example.com", "password123");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (!userCredentials.containsKey(oldEmail)) {
            System.out.println("Invalid email.");
            return;
        }
        
        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();
        if (!userCredentials.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        if (newEmail.isEmpty()) {
            System.out.println("New email cannot be empty.");
            return;
        }

        userCredentials.remove(oldEmail);
        userCredentials.put(newEmail, confirmPassword);
        System.out.println("Email changed successfully.");
    }
}