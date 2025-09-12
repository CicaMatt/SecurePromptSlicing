import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static final Map<String, String> users = new HashMap<>();

    static {
        users.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        if (!users.containsKey(oldEmail)) {
            System.out.println("The provided email does not exist.");
            return;
        }

        System.out.print("Enter your confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password. Please try again.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        if (newEmail.equals(oldEmail)) {
            System.out.println("New email cannot be the same as the old email.");
            return;
        }

        if (users.containsKey(newEmail)) {
            System.out.println("The new email is already in use. Please choose a different one.");
            return;
        }

        users.put(newEmail, users.remove(oldEmail));
        System.out.println("Your email has been successfully changed to " + newEmail);
    }
}