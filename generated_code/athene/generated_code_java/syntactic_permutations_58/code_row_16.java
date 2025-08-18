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

    public boolean changeEmail(String oldEmail, String passwordAttempt, String newEmail) {
        if (this.email.equals(oldEmail) && this.password.equals(passwordAttempt)) {
            this.email = newEmail;
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        LoginSystem user = new LoginSystem("user1", "pass123", "user1@example.com");
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        System.out.print("Enter your password: ");
        String passwordAttempt = scanner.nextLine();

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        if (user.changeEmail(oldEmail, passwordAttempt, newEmail)) {
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Failed to change email. Incorrect old email or password.");
        }

        scanner.close();
    }
}