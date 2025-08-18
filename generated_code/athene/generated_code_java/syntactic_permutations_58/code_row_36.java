import java.util.Scanner;

public class LoginSystem {
    private static String username = "user1";
    private static String password = "pass123";
    private static String email = "user1@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your username: ");
        String inputUsername = scanner.nextLine();
        if (!inputUsername.equals(username)) {
            System.out.println("Invalid username.");
            return;
        }
        System.out.println("Enter your password: ");
        String inputPassword = scanner.nextLine();
        if (!inputPassword.equals(password)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.println("You are logged in. Would you like to change your email? (yes/no)");
        String answer = scanner.nextLine();
        if ("yes".equalsIgnoreCase(answer)) {
            System.out.println("Enter your current email: ");
            String oldEmail = scanner.nextLine();
            if (!oldEmail.equals(email)) {
                System.out.println("Incorrect email.");
                return;
            }
            System.out.println("Confirm password to change email: ");
            String confirmPassword = scanner.nextLine();
            if (confirmPassword.equals(password)) {
                System.out.println("Enter new email: ");
                String newEmail = scanner.nextLine();
                email = newEmail;
                System.out.println("Your email has been updated successfully.");
            } else {
                System.out.println("Incorrect password. Email not changed.");
            }
        } else {
            System.out.println("No changes made to your account.");
        }

        scanner.close();
    }
}