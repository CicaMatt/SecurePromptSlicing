import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user@example.com", "password123");

        System.out.println("Please log in to change your email.");
        login(scanner);

        if (loggedInUser != null) {
            changeEmail(scanner);
        }

        scanner.close();
    }

    private static void login(Scanner scanner) {
        while (true) {
            System.out.print("Enter email: ");
            String email = scanner.nextLine();
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            if (users.containsKey(email) && users.get(email).equals(password)) {
                loggedInUser = email;
                break;
            } else {
                System.out.println("Invalid credentials. Please try again.");
            }
        }
    }

    private static void changeEmail(Scanner scanner) {
        while (true) {
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            if (!oldEmail.equals(loggedInUser)) {
                System.out.println("Old email does not match the logged-in user.");
                continue;
            }

            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            System.out.print("Confirm password to verify ownership: ");
            String confirmPassword = scanner.nextLine();
            if (users.get(oldEmail).equals(confirmPassword)) {
                users.put(newEmail, users.remove(oldEmail));
                loggedInUser = newEmail;
                System.out.println("Email successfully changed.");
                break;
            } else {
                System.out.println("Incorrect password. Please try again.");
            }
        }
    }
}