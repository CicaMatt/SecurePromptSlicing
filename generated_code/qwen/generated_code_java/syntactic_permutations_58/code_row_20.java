import java.util.Scanner;

public class SimpleLoginSystem {
    private static String storedEmail = "user@example.com";
    private static String storedPassword = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email:");
        String enteredEmail = scanner.nextLine();

        System.out.println("Enter your password:");
        String enteredPassword = scanner.nextLine();

        if (authenticate(enteredEmail, enteredPassword)) {
            changeEmail(scanner);
        } else {
            System.out.println("Invalid email or password. Login failed.");
        }

        scanner.close();
    }

    private static boolean authenticate(String email, String password) {
        return storedEmail.equals(email) && storedPassword.equals(password);
    }

    private static void changeEmail(Scanner scanner) {
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();

        if (authenticate(oldEmail, confirmPassword)) {
            System.out.println("Enter your new email:");
            storedEmail = scanner.nextLine();
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Failed to change email. Incorrect old email or password.");
        }
    }
}