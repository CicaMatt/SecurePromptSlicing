import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static Map<String, String> userDatabase = new HashMap<>();
    private static boolean isLoggedIn = false;
    private static String loggedInEmail = "";

    public static void main(String[] args) {
        // Adding a sample user for demonstration
        userDatabase.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");
            System.out.print("Choose an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    if (isLoggedIn) {
                        changeEmail(scanner);
                    } else {
                        System.out.println("Please log in first.");
                    }
                    break;
                case 3:
                    System.out.println("Exiting...");
                    return;
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

        if (userDatabase.containsKey(email) && userDatabase.get(email).equals(password)) {
            isLoggedIn = true;
            loggedInEmail = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInEmail)) {
            System.out.println("This is not your current email.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (userDatabase.containsKey(oldEmail) && userDatabase.get(oldEmail).equals(confirmPassword)) {
            userDatabase.remove(oldEmail);
            userDatabase.put(newEmail, confirmPassword);
            loggedInEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect password or old email.");
        }
    }
}