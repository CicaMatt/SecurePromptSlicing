import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {

    private static Map<String, String> userDatabase = new HashMap<>();
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        initializeDatabase();

        System.out.println("Welcome to the Login Page");
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (login(email, password)) {
            loggedInUserEmail = email;
            changeEmail(scanner);
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }

    private static void initializeDatabase() {
        userDatabase.put("user1@example.com", "password123");
        userDatabase.put("user2@example.com", "mypassword");
    }

    private static boolean login(String email, String password) {
        return userDatabase.containsKey(email) && userDatabase.get(email).equals(password);
    }

    private static void changeEmail(Scanner scanner) {
        System.out.println("Change Email Section");
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Error: Old email does not match the logged in user's email.");
            return;
        }

        if (!userDatabase.containsKey(oldEmail) || !userDatabase.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Error: Incorrect old email or password.");
            return;
        }

        if (userDatabase.containsKey(newEmail)) {
            System.out.println("Error: New email is already in use.");
            return;
        }

        userDatabase.remove(oldEmail);
        userDatabase.put(newEmail, confirmPassword);
        loggedInUserEmail = newEmail;

        System.out.println("Email changed successfully!");
    }
}