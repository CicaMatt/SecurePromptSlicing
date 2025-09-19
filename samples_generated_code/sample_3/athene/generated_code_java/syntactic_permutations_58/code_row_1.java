import java.util.Scanner;

public class LoginSystem {
    private static String username = "user";
    private static String password = "password123";
    private static String email = "user@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String enteredUsername = scanner.nextLine();
        System.out.print("Enter password: ");
        String enteredPassword = scanner.nextLine();

        if (authenticate(enteredUsername, enteredPassword)) {
            System.out.println("Login successful!");
            changeEmail(scanner);
        } else {
            System.out.println("Invalid credentials. Login failed.");
        }

        scanner.close();
    }

    private static boolean authenticate(String username, String password) {
        return this.username.equals(username) && this.password.equals(password);
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm your password to change email: ");
        String confirmPassword = scanner.nextLine();

        if (oldEmail.equals(email) && confirmPassword.equals(password)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            email = newEmail;
            System.out.println("Email changed successfully. New email: " + email);
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }
    }
}