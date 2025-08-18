import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static Map<String, String> userCredentials = new HashMap<>();

    static {
        // Pre-populate with a sample user
        userCredentials.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        System.out.println("Enter your confirm password:");
        String confirmPassword = scanner.nextLine();

        if (isValidUser(oldEmail, confirmPassword)) {
            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();
            changeEmail(oldEmail, newEmail);
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Invalid old email or confirm password.");
        }
    }

    private static boolean isValidUser(String email, String password) {
        return userCredentials.containsKey(email) && userCredentials.get(email).equals(password);
    }

    private static void changeEmail(String oldEmail, String newEmail) {
        if (userCredentials.containsKey(oldEmail)) {
            String password = userCredentials.remove(oldEmail);
            userCredentials.put(newEmail, password);
        }
    }
}