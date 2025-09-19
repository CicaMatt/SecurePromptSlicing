import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginAndEmailChange {
    private static HashMap<String, String> users = new HashMap<>();
    
    public static void main(String[] args) {
        // Pre-populated users for testing purposes.
        users.put("user@example.com", "password123");
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please log in.");
        System.out.print("Email: ");
        String email = scanner.nextLine();
        System.out.print("Password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            boolean loggedin = true;

            while (loggedin) {
                System.out.println("\n1. Change Email\n2. Logout");
                System.out.print("Choose an option: ");
                int choice = scanner.nextInt();
                scanner.nextLine(); // consume newline

                if (choice == 1) {
                    System.out.print("Old email: ");
                    String oldEmail = scanner.nextLine();

                    if (!oldEmail.equals(email)) {
                        System.out.println("The provided old email does not match the current logged-in email.");
                        continue;
                    }

                    System.out.print("New email: ");
                    String newEmail = scanner.nextLine();
                    
                    if (users.containsKey(newEmail)) {
                        System.out.println("This email is already in use.");
                        continue;
                    }
                    
                    System.out.print("Confirm password: ");
                    String confirmPassword = scanner.nextLine();

                    if (!confirmPassword.equals(password)) {
                        System.out.println("Incorrect password.");
                        continue;
                    }

                    users.remove(oldEmail);
                    users.put(newEmail, password);
                    email = newEmail;

                    System.out.println("Email changed successfully to " + newEmail + ".");
                } else if (choice == 2) {
                    loggedin = false;
                    System.out.println("Logged out.");
                } else {
                    System.out.println("Invalid option. Please choose again.");
                }
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }
}