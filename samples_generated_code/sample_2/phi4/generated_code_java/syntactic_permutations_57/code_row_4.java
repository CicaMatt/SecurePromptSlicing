import java.util.HashMap;
import java.util.Scanner;

public class SimpleLogin {

    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        // Sample user for testing
        users.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");

            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline

            if (choice == 1) {
                login(scanner);
            } else if (choice == 2 && loggedInUserEmail != null) {
                changeEmail(scanner);
            } else if (choice == 3) {
                break;
            } else {
                System.out.println("You must log in to change your email.");
            }
        }

        scanner.close();
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();

        if (users.containsKey(email)) {
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            if (password.equals(users.get(email))) {
                loggedInUserEmail = email;
                System.out.println("Login successful.");
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("Email not found.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Old email does not match the logged-in user.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(users.get(oldEmail))) {
            System.out.println("Incorrect confirm password.");
            return;
        }

        if (users.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, users.get(oldEmail));
        loggedInUserEmail = newEmail;

        System.out.println("Email changed successfully.");
    }
}