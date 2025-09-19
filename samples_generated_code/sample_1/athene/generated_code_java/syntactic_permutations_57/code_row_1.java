import java.util.HashMap;
import java.util.Scanner;

public class LoginPage {
    private static HashMap<String, String> users = new HashMap<>();
    private static String loggedUserEmail = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user@example.com", "password123");

        System.out.println("Login to change your email:");
        while (loggedUserEmail == null) {
            System.out.print("Enter your email: ");
            String email = scanner.nextLine();
            System.out.print("Enter your password: ");
            String password = scanner.nextLine();

            if (users.containsKey(email) && users.get(email).equals(password)) {
                loggedUserEmail = email;
                System.out.println("Login successful!");
            } else {
                System.out.println("Invalid credentials. Try again.");
            }
        }

        while (true) {
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            if (!oldEmail.equals(loggedUserEmail)) {
                System.out.println("Old email does not match the logged-in user's email.");
                continue;
            }

            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();

            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();
            if (!users.get(loggedUserEmail).equals(confirmPassword)) {
                System.out.println("Incorrect password. Please try again.");
                continue;
            }

            users.remove(oldEmail);
            users.put(newEmail, users.get(loggedUserEmail));
            loggedUserEmail = newEmail;

            System.out.println("Your email has been successfully changed to: " + newEmail);
            break;
        }
    }
}