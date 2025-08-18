import java.util.Scanner;
import java.util.Map;
import java.util.HashMap;

public class EmailChangePage {
    private static Map<String, String> users = new HashMap<>();
    private static String loggedInUser;

    public static void main(String[] args) {
        // Simulate existing users with email and password
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");

        Scanner scanner = new Scanner(System.in);

        System.out.println("Login to change your email:");
        System.out.print("Email: ");
        String loginEmail = scanner.nextLine();
        System.out.print("Password: ");
        String loginPassword = scanner.nextLine();

        if (login(loginEmail, loginPassword)) {
            System.out.println("Logged in successfully. You can now change your email.");
            changeEmail(scanner);
        } else {
            System.out.println("Login failed. Please try again.");
        }

        scanner.close();
    }

    private static boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            return true;
        }
        return false;
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password to verify ownership: ");
        String confirmPassword = scanner.nextLine();

        if (oldEmail.equals(loggedInUser) && users.get(oldEmail).equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            loggedInUser = newEmail;
            System.out.println("Your email has been changed successfully.");
        } else {
            System.out.println("Failed to change email. Please check your details and try again.");
        }
    }
}