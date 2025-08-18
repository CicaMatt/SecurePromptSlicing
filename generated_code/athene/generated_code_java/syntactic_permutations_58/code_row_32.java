import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static final HashMap<String, String> users = new HashMap<>();
    private static String currentUsername = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user1", "password1");
        users.put("user2", "password2");

        while (true) {
            System.out.println("Enter 1 to login, 2 to change email, 3 to exit:");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    System.out.println("Exiting...");
                    return;
                default:
                    System.out.println("Invalid choice, try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(username) && users.get(username).equals(password)) {
            currentUsername = username;
            System.out.println("Logged in successfully.");
        } else {
            System.out.println("Invalid username or password.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (currentUsername == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(currentUsername) && users.get(currentUsername).equals(password)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            // Assuming email is stored in a separate map for simplicity
            HashMap<String, String> emails = new HashMap<>();
            if (emails.containsKey(oldEmail)) {
                emails.put(newEmail, currentUsername);
                emails.remove(oldEmail);
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Incorrect old email.");
            }
        } else {
            System.out.println("Incorrect password.");
        }
    }
}