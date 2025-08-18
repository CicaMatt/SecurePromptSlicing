import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Simulate logged-in user with old email and password
        users.put("user@example.com", "password123");
        
        System.out.println("Welcome to the Email Change Service!");
        changeEmail();
    }

    private static void changeEmail() {
        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();

        if (!users.containsKey(oldEmail)) {
            System.out.println("This email is not registered.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm your password to verify ownership: ");
        String confirmPassword = scanner.nextLine();

        if (users.get(oldEmail).equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            System.out.println("Your email has been successfully changed to " + newEmail);
        } else {
            System.out.println("Incorrect password. Email change failed.");
        }
    }
}