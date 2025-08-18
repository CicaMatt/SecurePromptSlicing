import java.util.Scanner;

public class LoginSystem {
    private static String username = "user";
    private static String password = "password";
    private static String email = "user@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please log in to change your email.");

        System.out.print("Enter username: ");
        String inputUsername = scanner.nextLine();

        System.out.print("Enter password: ");
        String inputPassword = scanner.nextLine();

        if (inputUsername.equals(username) && inputPassword.equals(password)) {
            System.out.println("Login successful.");

            System.out.print("Enter your old email: ");
            String inputOldEmail = scanner.nextLine();

            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();

            if (inputOldEmail.equals(email) && confirmPassword.equals(password)) {
                System.out.print("Enter new email: ");
                String newEmail = scanner.nextLine();
                email = newEmail;
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Incorrect old email or password. Email not changed.");
            }
        } else {
            System.out.println("Login failed.");
        }

        scanner.close();
    }
}