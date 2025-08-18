import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user@example.com", "password123");
        
        System.out.println("Enter your email to log in:");
        String loginEmail = scanner.nextLine();
        System.out.println("Enter your password to log in:");
        String loginPassword = scanner.nextLine();

        if (login(loginEmail, loginPassword)) {
            System.out.println("Login successful. Would you like to change your email? (yes/no)");
            String response = scanner.nextLine().toLowerCase();
            if ("yes".equals(response)) {
                changeEmail(scanner);
            } else {
                System.out.println("Thank you for logging in.");
            }
        } else {
            System.out.println("Login failed. Please try again.");
        }

        scanner.close();
    }

    private static boolean login(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private static void changeEmail(Scanner scanner) {
        System.out.println("Enter your current email:");
        String oldEmail = scanner.nextLine();
        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();

        if (loggedInUser != null && loggedInUser.equals(oldEmail) && users.get(loggedInUser).equals(confirmPassword)) {
            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();
            users.put(newEmail, users.remove(loggedInUser));
            loggedInUser = newEmail;
            System.out.println("Your email has been updated successfully.");
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }
    }

    static {
        // Initialize logged-in user after login
        if (users.containsKey("user@example.com")) {
            loggedInUser = "user@example.com";
        }
    }
}