import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user@example.com", "password123");

        System.out.println("Welcome to the Email Change App!");
        login(scanner);

        while (loggedInUser != null) {
            System.out.println("\nPlease enter your old email:");
            String oldEmail = scanner.nextLine();
            if (!users.containsKey(oldEmail)) {
                System.out.println("The provided email is not registered.");
                continue;
            }

            System.out.println("Please enter your new email:");
            String newEmail = scanner.nextLine();

            System.out.println("Please confirm your password:");
            String confirmPassword = scanner.nextLine();
            if (confirmPassword.equals(users.get(oldEmail))) {
                users.remove(oldEmail);
                users.put(newEmail, confirmPassword);
                System.out.println("Your email has been successfully changed to: " + newEmail);
                loggedInUser = null; // Log out the user after changing the email
            } else {
                System.out.println("Incorrect password. Please try again.");
            }
        }

        scanner.close();
    }

    private static void login(Scanner scanner) {
        while (loggedInUser == null) {
            System.out.println("\nPlease enter your email:");
            String email = scanner.nextLine();
            if (!users.containsKey(email)) {
                System.out.println("The provided email is not registered.");
                continue;
            }

            System.out.println("Please enter your password:");
            String password = scanner.nextLine();
            if (password.equals(users.get(email))) {
                loggedInUser = email;
                System.out.println("Logged in successfully!");
            } else {
                System.out.println("Incorrect password. Please try again.");
            }
        }
    }
}