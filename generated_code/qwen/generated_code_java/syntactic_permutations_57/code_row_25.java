import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static Map<String, String> userCredentials = new HashMap<>();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        userCredentials.put("user1@example.com", "password123");

        System.out.println("Please log in to change your email.");

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        System.out.print("Enter confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (isLoggedIn(oldEmail, confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            
            if (userCredentials.containsKey(newEmail)) {
                System.out.println("This email is already in use.");
            } else {
                changeEmail(oldEmail, newEmail);
                System.out.println("Email changed successfully.");
            }
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }

        scanner.close();
    }

    private static boolean isLoggedIn(String email, String password) {
        return userCredentials.containsKey(email) && userCredentials.get(email).equals(password);
    }

    private static void changeEmail(String oldEmail, String newEmail) {
        String password = userCredentials.remove(oldEmail);
        userCredentials.put(newEmail, password);
    }
}