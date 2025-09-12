import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class EmailChangeApp {
    private static final Map<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        initializeUsers();
        
        System.out.println("Login to change your email:");
        login(scanner);

        if (loggedInUser != null) {
            changeEmail(scanner);
        } else {
            System.out.println("Login failed. Exiting...");
        }

        scanner.close();
    }

    private static void initializeUsers() {
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUser)) {
            System.out.println("Old email does not match the logged-in user.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm password to verify ownership: ");
        String confirmPassword = scanner.nextLine();
        if (!users.get(loggedInUser).equals(confirmPassword)) {
            System.out.println("Incorrect password. Email change failed.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);
        loggedInUser = newEmail;

        System.out.println("Your email has been successfully changed to: " + newEmail);
    }
}