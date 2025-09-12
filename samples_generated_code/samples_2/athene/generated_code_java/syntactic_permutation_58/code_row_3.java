import java.util.Scanner;

public class LoginSystem {
    private static String username = "user1";
    private static String password = "pass123";
    private static String email = "user1@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your username: ");
        String inputUsername = scanner.nextLine();
        System.out.print("Enter your password: ");
        String inputPassword = scanner.nextLine();

        if (inputUsername.equals(username) && inputPassword.equals(password)) {
            System.out.println("Logged in successfully.");
            changeEmail(scanner);
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String inputOldEmail = scanner.nextLine();
        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (inputOldEmail.equals(email) && confirmPassword.equals(password)) {
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            email = newEmail;
            System.out.println("Email updated successfully.");
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }
    }
}