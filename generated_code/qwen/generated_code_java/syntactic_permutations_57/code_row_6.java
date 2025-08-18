import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class EmailChangeSystem {

    private static Map<String, String> users = new HashMap<>();
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Sample user data
        users.put("user@example.com", "password123");

        System.out.println("Login to change your email.");
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (login(oldEmail, password)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();

            changeEmail(oldEmail, newEmail, confirmPassword);
        } else {
            System.out.println("Login failed. Please try again.");
        }

        scanner.close();
    }

    private static boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUserEmail = email;
            return true;
        }
        return false;
    }

    private static void changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("You are not logged in with the provided old email.");
            return;
        }

        if (!users.containsKey(oldEmail)) {
            System.out.println("The provided old email does not exist.");
            return;
        }

        if (!users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);
        loggedInUserEmail = newEmail;

        System.out.println("Email changed successfully to: " + newEmail);
    }
}