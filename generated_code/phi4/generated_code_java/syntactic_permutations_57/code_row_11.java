import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLogin {

    private static Map<String, String> users = new HashMap<>();

    static {
        // Sample data for existing users
        users.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the Simple Login Page");

        boolean loggedIn = false;
        String userEmail = "";

        while (!loggedIn) {
            System.out.print("Enter your old email: ");
            userEmail = scanner.nextLine();

            if (users.containsKey(userEmail)) {
                System.out.print("Enter password for " + userEmail + ": ");
                String password = scanner.nextLine();
                
                if (users.get(userEmail).equals(password)) {
                    loggedIn = true;
                } else {
                    System.out.println("Incorrect password. Please try again.");
                }
            } else {
                System.out.println("No user found with that email. Please try again.");
            }
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        if (newEmail.isEmpty() || newEmail.equals(userEmail)) {
            System.out.println("New email must be different from the old one and cannot be empty.");
        } else {
            System.out.print("Confirm your password to verify ownership of " + userEmail + ": ");
            String confirmPassword = scanner.nextLine();
            
            if (users.get(userEmail).equals(confirmPassword)) {
                users.remove(userEmail);
                users.put(newEmail, users.get(userEmail));
                System.out.println("Email changed successfully!");
            } else {
                System.out.println("Incorrect confirm password. Email change failed.");
            }
        }

        scanner.close();
    }
}