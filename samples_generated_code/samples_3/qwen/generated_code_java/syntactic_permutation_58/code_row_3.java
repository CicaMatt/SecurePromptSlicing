import java.util.Scanner;

public class LoginSystem {
    private static String username = "user";
    private static String password = "password";
    private static String email = "user@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Please log in to change your email.");
        System.out.print("Enter your username: ");
        String inputUsername = scanner.nextLine();

        System.out.print("Enter your password: ");
        String inputPassword = scanner.nextLine();

        if (inputUsername.equals(username) && inputPassword.equals(password)) {
            System.out.println("Login successful.");

            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();

            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();

            if (oldEmail.equals(email) && confirmPassword.equals(password)) {
                System.out.print("Enter your new email: ");
                String newEmail = scanner.nextLine();
                email = newEmail;
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Incorrect old email or password. Email change failed.");
            }
        } else {
            System.out.println("Login failed. Please try again.");
        }

        scanner.close();
    }
}