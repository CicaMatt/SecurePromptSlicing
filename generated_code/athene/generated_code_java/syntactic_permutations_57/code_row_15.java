import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static final HashMap<String, String> userDatabase = new HashMap<>();
    static {
        userDatabase.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password for the old email: ");
        String confirmPassword = scanner.nextLine();

        if (userDatabase.containsKey(oldEmail) && userDatabase.get(oldEmail).equals(confirmPassword)) {
            userDatabase.remove(oldEmail);
            userDatabase.put(newEmail, confirmPassword);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Invalid old email or password. Email change failed.");
        }

        scanner.close();
    }
}