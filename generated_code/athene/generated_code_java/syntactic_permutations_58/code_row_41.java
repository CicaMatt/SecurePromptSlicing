import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");

        while (true) {
            System.out.println("1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

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
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter current email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter current password: ");
        String password = scanner.nextLine();
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        if (loggedInUser.equals(oldEmail) && users.get(loggedInUser).equals(password)) {
            users.remove(loggedInUser);
            users.put(newEmail, password);
            loggedInUser = newEmail;
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Incorrect old email or password.");
        }
    }
}