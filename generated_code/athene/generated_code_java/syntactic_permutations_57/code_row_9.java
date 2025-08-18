import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Simulate existing user data
        users.put("user@example.com", "password123");

        System.out.println("Welcome to the Email Change App!");
        while (true) {
            System.out.print("Enter your email: ");
            String oldEmail = scanner.nextLine();
            if (!users.containsKey(oldEmail)) {
                System.out.println("Email does not exist. Please try again.");
                continue;
            }

            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();

            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();

            if (users.get(oldEmail).equals(confirmPassword)) {
                users.remove(oldEmail);
                users.put(newEmail, confirmPassword);
                System.out.println("Email changed successfully!");
                break;
            } else {
                System.out.println("Incorrect password. Please try again.");
            }
        }

        scanner.close();
    }
}