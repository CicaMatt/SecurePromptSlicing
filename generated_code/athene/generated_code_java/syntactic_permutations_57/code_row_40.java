import java.util.Scanner;
import java.util.HashMap;

public class ChangeEmailPage {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user@example.com", "password123");

        System.out.println("Please log in with your email and password.");
        login(scanner);

        if (loggedInUser != null) {
            changeEmail(scanner);
        }

        scanner.close();
    }

    private static void login(Scanner scanner) {
        while (true) {
            System.out.print("Email: ");
            String email = scanner.nextLine();
            System.out.print("Password: ");
            String password = scanner.nextLine();

            if (users.containsKey(email) && users.get(email).equals(password)) {
                loggedInUser = email;
                break;
            } else {
                System.out.println("Invalid email or password. Please try again.");
            }
        }
    }

    private static void changeEmail(Scanner scanner) {
        while (true) {
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            System.out.print("Confirm password to verify ownership: ");
            String confirmPassword = scanner.nextLine();

            if (loggedInUser.equals(oldEmail) && users.get(loggedInUser).equals(confirmPassword)) {
                users.remove(oldEmail);
                users.put(newEmail, confirmPassword);
                System.out.println("Your email has been successfully changed.");
                loggedInUser = newEmail;
                break;
            } else {
                System.out.println("Incorrect old email or password. Please try again.");
            }
        }
    }
}