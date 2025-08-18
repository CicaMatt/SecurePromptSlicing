import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static Map<String, String> userDatabase = new HashMap<>();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        userDatabase.put("user@example.com", "password123");

        System.out.println("Login to change your email:");
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (authenticate(oldEmail, confirmPassword)) {
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();

            if (!newEmail.equals(oldEmail) && !userDatabase.containsKey(newEmail)) {
                changeEmail(oldEmail, newEmail);
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("New email must be different and not already in use.");
            }
        } else {
            System.out.println("Authentication failed. Incorrect email or password.");
        }

        scanner.close();
    }

    private static boolean authenticate(String email, String password) {
        return userDatabase.containsKey(email) && userDatabase.get(email).equals(password);
    }

    private static void changeEmail(String oldEmail, String newEmail) {
        String password = userDatabase.remove(oldEmail);
        userDatabase.put(newEmail, password);
    }
}