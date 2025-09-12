import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginPage {

    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static boolean loggedIn = false;
    private static String currentUserEmail = null;

    public static void main(String[] args) {
        // Predefined user for demonstration
        users.put("user@example.com", "password123");

        while (true) {
            System.out.println("\n1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline

            switch (choice) {
                case 1:
                    login();
                    break;
                case 2:
                    if (loggedIn) {
                        changeEmail();
                    } else {
                        System.out.println("Please log in first.");
                    }
                    break;
                case 3:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void login() {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedIn = true;
            currentUserEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail() {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(currentUserEmail)) {
            System.out.println("Old email does not match the logged-in user.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        
        if (users.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return;
        }

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect confirm password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, users.get(oldEmail));
        currentUserEmail = newEmail;

        System.out.println("Email changed successfully!");
    }
}