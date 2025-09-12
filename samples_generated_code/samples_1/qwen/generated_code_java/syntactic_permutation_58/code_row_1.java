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

    public boolean login(String inputUsername, String inputPassword) {
        return this.username.equals(inputUsername) && this.password.equals(inputPassword);
    }

    public void changeEmail(String oldEmail, String confirmPassword, String newEmail) {
        if (this.email.equals(oldEmail) && this.password.equals(confirmPassword)) {
            this.email = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Failed to change email. Incorrect old email or password.");
        }
    }

    public static void main(String[] args) {
        LoginSystem user = new LoginSystem("testuser", "testpassword", "oldemail@example.com");
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String inputUsername = scanner.nextLine();
        System.out.print("Enter password: ");
        String inputPassword = scanner.nextLine();

        if (user.login(inputUsername, inputPassword)) {
            System.out.println("Logged in successfully.");
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            user.changeEmail(oldEmail, confirmPassword, newEmail);
        } else {
            System.out.println("Login failed.");
        }

        scanner.close();
    }
}