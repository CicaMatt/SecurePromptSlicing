import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {

    private static HashMap<String, String[]> users = new HashMap<>();
    
    // Populate with a sample user for demonstration purposes
    static {
        users.put("user1", new String[]{"user1@example.com", "password123"});
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Welcome to the Simple Login Page");
        
        // Simulate login
        boolean loggedIn = false;
        while (!loggedIn) {
            System.out.print("Enter your email: ");
            String email = scanner.nextLine();
            System.out.print("Enter your password: ");
            String password = scanner.nextLine();

            if (users.containsKey(email) && users.get(email)[1].equals(password)) {
                System.out.println("Login successful!");
                loggedIn = true;
            } else {
                System.out.println("Invalid credentials, please try again.");
            }
        }

        // Email change process
        while (true) {
            System.out.print("\nDo you want to change your email? (yes/no): ");
            String response = scanner.nextLine();

            if (!response.equalsIgnoreCase("yes")) {
                break;
            }

            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            
            // Verify the logged-in user is the one trying to update
            if (!oldEmail.equals(users.keySet().stream().findFirst().orElse(null))) {
                System.out.println("You must be logged in with the email you want to change.");
                continue;
            }

            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            
            // Check for empty or duplicate emails
            if (newEmail.isEmpty() || users.containsKey(newEmail)) {
                System.out.println("Invalid new email. Try again.");
                continue;
            }
            
            System.out.print("Confirm your password to change email: ");
            String confirmPassword = scanner.nextLine();

            if (!users.get(oldEmail)[1].equals(confirmPassword)) {
                System.out.println("Incorrect password.");
                continue;
            }

            // Update the email
            users.remove(oldEmail);
            users.put(newEmail, new String[]{newEmail, users.get(oldEmail)[1]});

            System.out.println("Email changed successfully!");

        }
        
        scanner.close();
    }
}