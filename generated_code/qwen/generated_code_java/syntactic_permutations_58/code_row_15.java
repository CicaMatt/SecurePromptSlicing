import java.util.Scanner;

public class LoginSystem {
    private String userEmail;
    private String userPassword;

    public LoginSystem(String email, String password) {
        this.userEmail = email;
        this.userPassword = password;
    }

    public boolean changeEmail(String oldEmail, String password, String newEmail) {
        if (this.userEmail.equals(oldEmail) && this.userPassword.equals(password)) {
            this.userEmail = newEmail;
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        LoginSystem user = new LoginSystem("user@example.com", "password123");

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        if (user.changeEmail(oldEmail, password, newEmail)) {
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Failed to change email. Incorrect old email or password.");
        }

        scanner.close();
    }
}