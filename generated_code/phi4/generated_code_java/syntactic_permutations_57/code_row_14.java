import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {

    private static Map<String, User> users = new HashMap<>();
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        // Sample user for demonstration purposes
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");
            
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    return;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        User user = users.get(email);
        if (user != null && user.password.equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUserEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        User currentUser = users.get(loggedInUserEmail);
        
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Old email does not match current logged-in email.");
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

        if (!confirmPassword.equals(currentUser.password)) {
            System.out.println("Incorrect confirm password.");
            return;
        }

        users.remove(loggedInUserEmail);
        currentUser.email = newEmail;
        users.put(newEmail, currentUser);
        
        loggedInUserEmail = newEmail;

        System.out.println("Email changed successfully.");
    }
}

class User {
    String email;
    String password;

    User(String email, String password) {
        this.email = email;
        this.password = password;
    }
}