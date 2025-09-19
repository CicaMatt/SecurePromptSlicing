import java.util.Scanner;

public class LoginSystem {
    private String username = "user";
    private String password = "pass123";
    private String email = "user@example.com";

    public boolean login(String username, String password) {
        return this.username.equals(username) && this.password.equals(password);
    }

    public void changeEmail() {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (email.equals(oldEmail) && this.password.equals(confirmPassword)) {
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            email = newEmail;
            System.out.println("Your email has been updated to: " + email);
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (loginSystem.login(username, password)) {
            System.out.println("Logged in successfully.");
            loginSystem.changeEmail();
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }
    }
}