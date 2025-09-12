import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginWithEmailChange {

    private static final HashMap<String, String> users = new HashMap<>();
    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Pre-populated user data for demonstration purposes.
        users.put("user@example.com", "password123");

        System.out.println("Welcome to the Simple Login Page!");

        while (true) {
            System.out.print("Enter email: ");
            String email = scanner.nextLine();
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            if (users.containsKey(email) && users.get(email).equals(password)) {
                System.out.println("Login successful!");
                
                while (true) {
                    System.out.println("\n1. Change Email");
                    System.out.println("2. Logout");
                    System.out.print("Choose an option: ");
                    
                    int choice = scanner.nextInt();
                    scanner.nextLine(); // Consume newline

                    if (choice == 1) {
                        changeEmail(email);
                    } else if (choice == 2) {
                        break;
                    } else {
                        System.out.println("Invalid option. Please try again.");
                    }
                }

            } else {
                System.out.println("Invalid email or password. Try again.");
            }
        }
    }

    private static void changeEmail(String currentEmail) {
        System.out.print("Enter old email (for confirmation): ");
        String oldEmail = scanner.nextLine();
        
        if (!currentEmail.equals(oldEmail)) {
            System.out.println("Old email does not match your login. Cannot proceed.");
            return;
        }
        
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        if (newEmail.equals(currentEmail)) {
            System.out.println("New email must be different from the old one.");
            return;
        }

        System.out.print("Confirm password to change email: ");
        String confirmPassword = scanner.nextLine();

        if (!users.get(currentEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password. Cannot proceed.");
            return;
        }
        
        users.remove(currentEmail);
        users.put(newEmail, confirmPassword);

        System.out.println("Email changed successfully!");

        // Update current email in session
        String updatedEmail = newEmail;
    }
}