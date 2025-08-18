import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        // Pre-populate with a sample user for demonstration purposes.
        users.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.println("\n1. Login\n2. Change Email\n3. Exit");
            System.out.print("Choose an option: ");
            int choice = Integer.parseInt(scanner.nextLine());
            
            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    System.exit(0);
                default:
                    System.out.println("Invalid option. Try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        if (loggedInUserEmail != null) {
            System.out.println("Already logged in as " + loggedInUserEmail);
            return;
        }

        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUserEmail == null) {
            System.out.println("Please login first.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Old email does not match the logged in user's email.");
            return;
        }

        if (users.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return;
        }

        if (!users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);
        loggedInUserEmail = newEmail;

        System.out.println("Email changed successfully to " + newEmail);
    }
}