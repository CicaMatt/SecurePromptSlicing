import java.util.HashMap;
import java.util.Scanner;

public class EmailChangeApp {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Simulate login
        System.out.print("Enter your email to log in: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            changeEmail(scanner);
        } else {
            System.out.println("Invalid credentials.");
        }

        scanner.close();
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

        System.out.print("Confirm your password to proceed: ");
        String confirmPassword = scanner.nextLine();
        if (!users.get(loggedInUser).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);
        loggedInUser = newEmail;

        System.out.println("Your email has been successfully changed to: " + newEmail);
    }
}