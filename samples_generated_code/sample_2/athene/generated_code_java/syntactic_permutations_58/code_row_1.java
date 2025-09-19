import java.util.Scanner;
import java.util.HashMap;

public class LoginSystem {
    private static HashMap<String, String> users = new HashMap<>();
    private static String currentUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user1@example.com", "password123");

        System.out.println("Enter your email to log in:");
        String loginEmail = scanner.nextLine();
        System.out.println("Enter your password to log in:");
        String loginPassword = scanner.nextLine();

        if (login(loginEmail, loginPassword)) {
            System.out.println("Login successful!");
            changeEmail(scanner);
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }

    private static boolean login(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private static void changeEmail(Scanner scanner) {
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        System.out.println("Enter your current password to confirm:");
        String confirmPassword = scanner.nextLine();

        if (currentUser != null && currentUser.equals(oldEmail) && users.get(currentUser).equals(confirmPassword)) {
            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();
            users.put(newEmail, users.remove(currentUser));
            currentUser = newEmail;
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }
    }
}