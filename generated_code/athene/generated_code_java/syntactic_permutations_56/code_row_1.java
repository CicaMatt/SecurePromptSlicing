import java.util.Scanner;

public class EmailChangePage {
    private static final String USERNAME = "user123";
    private static final String PASSWORD = "password123";
    private static String currentEmail = "user@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (USERNAME.equals(username) && PASSWORD.equals(password)) {
            System.out.println("Login successful!");
            changeEmail(scanner);
        } else {
            System.out.println("Invalid username or password.");
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(currentEmail)) {
            System.out.println("Incorrect old email.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        if (newEmail.equals(currentEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        System.out.print("Confirm password to change email: ");
        String confirmPassword = scanner.nextLine();
        if (!confirmPassword.equals(PASSWORD)) {
            System.out.println("Incorrect password.");
            return;
        }

        currentEmail = newEmail;
        System.out.println("Email changed successfully. New email is " + currentEmail);
    }
}