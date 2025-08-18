import java.util.HashMap;
import java.util.Scanner;

public class EmailChangeApp {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        // Simulate user login
        users.put("user@example.com", "password123");
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your email to log in: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (login(email, password)) {
            changeEmail(scanner);
        } else {
            System.out.println("Login failed. Please try again.");
        }

        scanner.close();
    }

    private static boolean login(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (loggedInUser != null && loggedInUser.equals(oldEmail) && users.get(loggedInUser).equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            System.out.println("Your email has been successfully changed.");
        } else {
            System.out.println("Failed to change email. Please check your inputs and try again.");
        }
    }

    static {
        // Simulate login for the user
        String initialEmail = "user@example.com";
        if (login(initialEmail, "password123")) {
            loggedInUser = initialEmail;
        }
    }
}