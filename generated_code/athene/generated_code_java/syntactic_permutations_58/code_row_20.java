import java.util.Scanner;

public class LoginSystem {
    private String username = "user1";
    private String password = "pass123";
    private String email = "user@example.com";

    public boolean login(String username, String password) {
        return this.username.equals(username) && this.password.equals(password);
    }

    public void changeEmail() {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(email)) {
            System.out.println("Incorrect old email.");
            return;
        }

        System.out.println("Confirm your password to proceed: ");
        String confirmPassword = scanner.nextLine();
        if (!confirmPassword.equals(password)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.println("Enter new email: ");
        String newEmail = scanner.nextLine();
        this.email = newEmail;
        System.out.println("Email successfully changed to " + newEmail);
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();

        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter username: ");
        String username = scanner.nextLine();
        System.out.println("Enter password: ");
        String password = scanner.nextLine();

        if (system.login(username, password)) {
            System.out.println("Login successful. You can now change your email.");
            system.changeEmail();
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }
    }
}