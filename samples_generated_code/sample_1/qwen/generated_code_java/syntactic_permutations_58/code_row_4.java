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

    public void changeEmail(String oldEmail, String password, String newEmail) {
        if (this.login(username, password) && this.email.equals(oldEmail)) {
            this.email = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Failed to change email. Incorrect old email or password.");
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        LoginSystem user = new LoginSystem("user123", "password123", "oldemail@example.com");

        System.out.print("Enter your username: ");
        String inputUsername = scanner.nextLine();

        System.out.print("Enter your password: ");
        String inputPassword = scanner.nextLine();

        if (user.login(inputUsername, inputPassword)) {
            System.out.println("Login successful.");

            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();

            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();

            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            user.changeEmail(oldEmail, confirmPassword, newEmail);
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }
}