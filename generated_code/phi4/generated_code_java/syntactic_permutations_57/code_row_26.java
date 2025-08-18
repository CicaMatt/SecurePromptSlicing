import java.util.HashMap;
import java.util.Scanner;

public class SimpleLogin {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Initialize with some dummy data
        users.put("user@example.com", "password123");

        System.out.println("Welcome to the Simple Login Page!");
        
        while (true) {
            System.out.print("Enter your email: ");
            String email = scanner.nextLine();
            
            if (!users.containsKey(email)) {
                System.out.println("Email not found. Please try again.");
                continue;
            }

            System.out.print("Enter your password: ");
            String password = scanner.nextLine();

            if (password.equals(users.get(email))) {
                while (true) {
                    System.out.println("Successfully logged in!");
                    System.out.println("1. Change Email");
                    System.out.println("2. Logout");

                    System.out.print("Choose an option: ");
                    int choice = Integer.parseInt(scanner.nextLine());

                    switch (choice) {
                        case 1:
                            changeEmail(email);
                            break;
                        case 2:
                            return;
                        default:
                            System.out.println("Invalid choice. Please try again.");
                    }
                }
            } else {
                System.out.println("Incorrect password. Please try again.");
            }
        }
    }

    private static void changeEmail(String currentEmail) {
        while (true) {
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();

            if (!oldEmail.equals(currentEmail)) {
                System.out.println("Old email does not match. Please try again.");
                continue;
            }

            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();

            if (users.containsKey(newEmail)) {
                System.out.println("New email already exists. Please choose a different one.");
                continue;
            }

            System.out.print("Re-enter your password for verification: ");
            String password = scanner.nextLine();

            if (!password.equals(users.get(currentEmail))) {
                System.out.println("Incorrect password. Please try again.");
                continue;
            }

            users.remove(currentEmail);
            users.put(newEmail, password);
            System.out.println("Email changed successfully!");

            break;
        }
    }
}