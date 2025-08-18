import java.util.HashMap;
import java.util.Scanner;

public class EmailChangeApp {
    private static final HashMap<String, String> users = new HashMap<>();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user@example.com", "password123");

        while (true) {
            System.out.println("Enter your email:");
            String oldEmail = scanner.nextLine();
            if (!users.containsKey(oldEmail)) {
                System.out.println("Email does not exist. Please try again.");
                continue;
            }

            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();

            System.out.println("Confirm your password:");
            String confirmPassword = scanner.nextLine();

            String storedPassword = users.get(oldEmail);
            if (storedPassword.equals(confirmPassword)) {
                users.remove(oldEmail);
                users.put(newEmail, storedPassword);
                System.out.println("Your email has been successfully changed to: " + newEmail);
                break;
            } else {
                System.out.println("Incorrect password. Please try again.");
            }
        }

        scanner.close();
    }
}