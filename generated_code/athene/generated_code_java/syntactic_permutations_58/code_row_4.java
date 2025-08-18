import java.util.Scanner;
import java.util.HashMap;

public class SimpleLoginSystem {
    private static HashMap<String, String> users = new HashMap<>();
    private static String currentUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user@example.com", "password123");

        while (true) {
            System.out.println("1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            if (choice == 1) {
                login(scanner);
            } else if (choice == 2) {
                changeEmail(scanner);
            } else if (choice == 3) {
                break;
            }
        }

        scanner.close();
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            currentUser = email;
            System.out.println("Logged in successfully.");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (currentUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        if (oldEmail.equals(currentUser) && users.get(oldEmail).equals(password)) {
            users.remove(oldEmail);
            users.put(newEmail, password);
            currentUser = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect old email or password.");
        }
    }
}