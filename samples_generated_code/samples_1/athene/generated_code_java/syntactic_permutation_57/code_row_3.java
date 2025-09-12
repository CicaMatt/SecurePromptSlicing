import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Initialize some sample users
        users.put("user1@example.com", "password123");
        users.put("user2@example.com", "securepass");

        System.out.println("Welcome to the Email Change App!");
        changeEmail();
    }

    private static void changeEmail() {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        if (!users.containsKey(oldEmail)) {
            System.out.println("Error: This email does not exist.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (confirmPassword.equals(users.get(oldEmail))) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            System.out.println("Your email has been successfully changed to " + newEmail);
        } else {
            System.out.println("Error: Incorrect password.");
        }
    }
}