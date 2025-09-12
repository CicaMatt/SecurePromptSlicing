import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginPage {

    private static HashMap<String, String> users = new HashMap<>();

    public static void main(String[] args) {
        // Pre-populate with a sample user for demonstration purposes.
        users.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.print("Enter your email: ");
            String oldEmail = scanner.nextLine();
            
            if (!users.containsKey(oldEmail)) {
                System.out.println("Invalid email. Please try again.");
                continue;
            }

            System.out.print("Enter your password: ");
            String inputPassword = scanner.nextLine();

            if (!inputPassword.equals(users.get(oldEmail))) {
                System.out.println("Incorrect password. Please try again.");
                continue;
            }
            
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            
            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();

            if (!confirmPassword.equals(inputPassword)) {
                System.out.println("Confirmation password does not match. Please try again.");
                continue;
            }

            users.remove(oldEmail);
            users.put(newEmail, inputPassword);

            System.out.println("Email changed successfully!");
        }
    }
}