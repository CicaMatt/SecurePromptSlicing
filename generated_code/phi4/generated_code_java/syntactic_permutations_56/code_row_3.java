import java.util.Scanner;

public class SimpleLogin {

    private static String currentUserEmail = "user@example.com";
    private static String currentPassword = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the Email Change Service");
        
        // Simulate user login
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (email.equals(currentUserEmail) && password.equals(currentPassword)) {
            System.out.println("Login successful.");
            changeEmail(scanner);
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(currentUserEmail)) {
            System.out.println("Old email does not match our records. Access denied.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        
        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old one.");
            return;
        }

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        System.out.print("Re-enter your password: ");
        String reEnterPassword = scanner.nextLine();

        if (!confirmPassword.equals(reEnterPassword)) {
            System.out.println("Passwords do not match. Please try again.");
            return;
        }

        // Assuming the passwords are correct
        if (reEnterPassword.equals(currentPassword)) {
            currentUserEmail = newEmail;
            currentPassword = reEnterPassword;  // Keeping it simple, just for demo purposes

            System.out.println("Email updated successfully. Your new email is: " + currentUserEmail);
        } else {
            System.out.println("Incorrect password. Email change failed.");
        }
    }
}