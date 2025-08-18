import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginPage {
    private static HashMap<String, String> users = new HashMap<>();
    
    public static void main(String[] args) {
        // Pre-populate with a sample user for demonstration purposes
        users.put("user@example.com", "confirm123");

        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the simple login page!");

        while (true) {
            System.out.print("Enter your email: ");
            String oldEmail = scanner.nextLine();

            if (!users.containsKey(oldEmail)) {
                System.out.println("Invalid email. Please try again.");
                continue;
            }

            System.out.print("Enter confirm code for " + oldEmail + ": ");
            String confirmCode = scanner.nextLine();

            if (!confirmCode.equals(users.get(oldEmail))) {
                System.out.println("Incorrect confirmation code. Access denied.");
                continue;
            }

            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (users.containsKey(newEmail)) {
                System.out.println("The new email already exists. Please try a different one.");
                continue;
            }

            System.out.print("Re-enter new email to confirm: ");
            String reEnteredNewEmail = scanner.nextLine();

            if (!newEmail.equals(reEnteredNewEmail)) {
                System.out.println("Mismatch in new emails entered. Try again.");
                continue;
            }

            users.remove(oldEmail);
            users.put(newEmail, "confirm123");

            System.out.println("Your email has been changed successfully.");

            break;
        }

        scanner.close();
    }
}