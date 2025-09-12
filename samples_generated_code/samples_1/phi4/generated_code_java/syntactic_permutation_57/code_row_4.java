import java.io.IOException;
import java.util.HashMap;
import java.util.Scanner;

public class SimpleLogin {

    private static HashMap<String, String> users = new HashMap<>();
    
    public static void main(String[] args) {
        // Sample user data for demonstration purposes.
        users.put("user1@example.com", "password123");
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Welcome to the Simple Login Page!");
        while (true) {
            System.out.print("Enter your email: ");
            String email = scanner.nextLine();
            
            if (!users.containsKey(email)) {
                System.out.println("Email not found. Please try again.");
                continue;
            }
            
            System.out.print("Enter your password: ");
            String password = scanner.nextLine();
            
            if (!password.equals(users.get(email))) {
                System.out.println("Incorrect password. Access denied.");
                continue;
            }
            
            System.out.println("Login successful!");
            changeEmail(scanner, email);
        }
    }

    private static void changeEmail(Scanner scanner, String oldEmail) {
        while (true) {
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            
            if (!newEmail.matches("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}")) {
                System.out.println("Invalid email format. Please try again.");
                continue;
            }
            
            if (users.containsKey(newEmail)) {
                System.out.println("This email is already in use. Please choose a different one.");
                continue;
            }
            
            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();
            
            if (!confirmPassword.equals(users.get(oldEmail))) {
                System.out.println("Incorrect confirm password. Access denied.");
                continue;
            }

            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);

            System.out.println("Your email has been changed successfully!");
            break;
        }
    }
}