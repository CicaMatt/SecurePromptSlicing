import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {

    private static Map<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("test@example.com", "password"); // Sample user

        while (true) {
            if (loggedInUser == null) {
                System.out.println("Please log in:");
                System.out.print("Email: ");
                String email = scanner.nextLine();
                System.out.print("Password: ");
                String password = scanner.nextLine();

                if (authenticate(email, password)) {
                    loggedInUser = email;
                    System.out.println("Logged in successfully!");
                } else {
                    System.out.println("Invalid email or password.");
                }
            } else {
                System.out.println("Options: 1. Change Email 2. Logout");
                int choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                switch (choice) {
                    case 1:
                        changeEmail(scanner);
                        break;
                    case 2:
                        loggedInUser = null;
                        System.out.println("Logged out.");
                        break;
                    default:
                        System.out.println("Invalid option.");
                }
            }
        }
    }

    private static boolean authenticate(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUser)) {
            System.out.println("This is not your current email.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        if (users.containsKey(newEmail)) {
            System.out.println("This email is already in use.");
            return;
        }

        System.out.print("Confirm your old email: ");
        String confirmEmail = scanner.nextLine();
        if (!confirmEmail.equals(loggedInUser)) {
            System.out.println("Email confirmation does not match.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, "password"); // Password remains same for simplicity
        loggedInUser = newEmail;
        System.out.println("Email changed successfully!");
    }
}