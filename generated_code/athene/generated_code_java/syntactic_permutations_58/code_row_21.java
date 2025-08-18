import java.util.Scanner;

public class LoginSystem {
    private static String username = "user";
    private static String password = "password123";
    private static String email = "user@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your username: ");
        String inputUsername = scanner.nextLine();
        System.out.print("Enter your password: ");
        String inputPassword = scanner.nextLine();

        if (inputUsername.equals(username) && inputPassword.equals(password)) {
            changeEmail(scanner);
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(email)) {
            System.out.println("Incorrect current email.");
            return;
        }
        
        System.out.print("Re-enter your password for confirmation: ");
        String confirmPassword = scanner.nextLine();
        if (!confirmPassword.equals(password)) {
            System.out.println("Incorrect password. Email change failed.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        email = newEmail;
        System.out.println("Your email has been successfully changed to " + newEmail);
    }
}