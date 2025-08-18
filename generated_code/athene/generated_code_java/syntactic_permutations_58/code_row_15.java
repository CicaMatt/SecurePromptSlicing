import java.util.Scanner;

public class LoginSystem {
    private String username;
    private String password;
    private String email;

    public LoginSystem(String username, String password, String email) {
        this.username = username;
        this.password = password;
        this.email = email;
    }

    public boolean changeEmail(String oldEmail, String confirmPassword, String newEmail) {
        if (this.email.equals(oldEmail) && this.password.equals(confirmPassword)) {
            this.email = newEmail;
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        LoginSystem user = new LoginSystem("user1", "password123", "user1@example.com");

        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        boolean success = user.changeEmail(oldEmail, confirmPassword, newEmail);

        if (success) {
            System.out.println("Your email has been successfully changed to " + newEmail);
        } else {
            System.out.println("Failed to change email. Please check your old email and password.");
        }

        scanner.close();
    }
}