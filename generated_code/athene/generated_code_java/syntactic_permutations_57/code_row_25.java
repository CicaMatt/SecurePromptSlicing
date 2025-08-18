import java.util.Scanner;
import java.util.HashMap;

public class EmailChangePage {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        setupDemoUsers();
        
        System.out.println("Welcome to the login page!");
        if (login(scanner)) {
            changeEmail(scanner);
        } else {
            System.out.println("Login failed. Exiting...");
        }
        scanner.close();
    }

    private static void setupDemoUsers() {
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");
    }

    private static boolean login(Scanner scanner) {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            return true;
        }
        return false;
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email to confirm: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUser)) {
            System.out.println("Old email does not match. Email change failed.");
            return;
        }

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();
        if (!users.get(loggedInUser).equals(confirmPassword)) {
            System.out.println("Incorrect password. Email change failed.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        if (users.containsKey(newEmail)) {
            System.out.println("This email is already in use. Please choose another one.");
            return;
        }

        users.put(newEmail, users.remove(loggedInUser));
        loggedInUser = newEmail;
        System.out.println("Your email has been successfully changed to: " + newEmail);
    }
}