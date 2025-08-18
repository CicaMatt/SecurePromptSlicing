import java.util.HashMap;
import java.util.Scanner;

public class LoginPage {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedUserEmail = null;

    public static void main(String[] args) {
        users.put("user@example.com", "password123");
        
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice, please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedUserEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedUserEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password to verify ownership: ");
        String confirmPassword = scanner.nextLine();

        if (users.get(loggedUserEmail).equals(confirmPassword)) {
            users.put(newEmail, users.remove(loggedUserEmail));
            loggedUserEmail = newEmail;
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Incorrect password. Email change failed.");
        }
    }
}