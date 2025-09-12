import java.util.Scanner;

public class LoginPage {
    private static final String USERNAME = "user";
    private static final String PASSWORD = "password123";
    private static String currentEmail = "user@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (authenticate(username, password)) {
            System.out.println("Login successful!");
            changeEmail(scanner);
        } else {
            System.out.println("Invalid credentials. Login failed.");
        }

        scanner.close();
    }

    private static boolean authenticate(String username, String password) {
        return USERNAME.equals(username) && PASSWORD.equals(password);
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter current password to confirm: ");
        String confirmPassword = scanner.nextLine();

        if (PASSWORD.equals(confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (!newEmail.equalsIgnoreCase(currentEmail)) {
                currentEmail = newEmail;
                System.out.println("Email changed successfully. New email: " + currentEmail);
            } else {
                System.out.println("New email must be different from the current email.");
            }
        } else {
            System.out.println("Incorrect password. Email change failed.");
        }
    }
}