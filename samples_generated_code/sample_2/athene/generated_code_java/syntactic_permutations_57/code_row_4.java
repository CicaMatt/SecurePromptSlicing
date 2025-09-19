import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class EmailChangePage {
    private static final Map<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Sample user data
        users.put("user@example.com", "password123");
        
        System.out.println("Login to change your email:");
        login(scanner);

        if (loggedInUser != null) {
            changeEmail(scanner);
        }

        scanner.close();
    }

    private static void login(Scanner scanner) {
        while (true) {
            System.out.print("Enter your email: ");
            String email = scanner.nextLine();
            System.out.print("Enter your password: ");
            String password = scanner.nextLine();

            if (users.containsKey(email) && users.get(email).equals(password)) {
                loggedInUser = email;
                break;
            } else {
                System.out.println("Invalid credentials. Please try again.");
            }
        }
    }

    private static void changeEmail(Scanner scanner) {
        while (true) {
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();

            if (!oldEmail.equals(loggedInUser)) {
                System.out.println("The provided old email does not match the logged-in user.");
            } else if (!users.get(oldEmail).equals(confirmPassword)) {
                System.out.println("Incorrect confirm password.");
            } else {
                users.put(newEmail, users.remove(oldEmail));
                loggedInUser = newEmail;
                System.out.println("Your email has been successfully changed to: " + newEmail);
                break;
            }
        }
    }
}