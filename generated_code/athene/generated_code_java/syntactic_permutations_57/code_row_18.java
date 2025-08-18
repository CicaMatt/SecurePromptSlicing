import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeSystem {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Initial user setup (for demonstration purposes)
        users.put("user@example.com", "password123");

        System.out.println("Welcome to the Email Change System");
        if (login()) {
            changeEmail();
        } else {
            System.out.println("Login failed. Exiting.");
        }

        scanner.close();
    }

    private static boolean login() {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            return true;
        }
        return false;
    }

    private static void changeEmail() {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (!users.containsKey(oldEmail)) {
            System.out.println("Old email does not exist.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();
        if (!users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);
        System.out.println("Your email has been successfully changed to " + newEmail);
    }
}