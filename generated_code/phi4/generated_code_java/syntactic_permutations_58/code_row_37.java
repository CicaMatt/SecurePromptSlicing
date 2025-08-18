import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {

    private static HashMap<String, String> users = new HashMap<>();
    private static String loggedInEmail = null;

    public static void main(String[] args) {
        // Predefined users for demonstration purposes
        users.put("user1@example.com", "password123");
        
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("\nWelcome to Simple Login System");
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");
            System.out.print("Choose an option: ");
            
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline

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
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        if (loggedInEmail != null) {
            System.out.println("You are already logged in.");
            return;
        }

        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInEmail = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!oldEmail.equals(loggedInEmail)) {
            System.out.println("Old email does not match the logged-in account.");
            return;
        }

        if (users.get(oldEmail).equals(confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            users.put(newEmail, confirmPassword);
            users.remove(oldEmail);
            loggedInEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect password. Email not changed.");
        }
    }
}