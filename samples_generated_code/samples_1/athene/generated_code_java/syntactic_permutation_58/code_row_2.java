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

    public void changeEmail() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (this.email.equals(oldEmail) && this.password.equals(confirmPassword)) {
            System.out.print("Enter your new email: ");
            this.email = scanner.nextLine();
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }
    }

    public static void main(String[] args) {
        LoginSystem user = new LoginSystem("john_doe", "securepassword123", "john@example.com");

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username to login: ");
        String inputUsername = scanner.nextLine();
        System.out.print("Enter password to login: ");
        String inputPassword = scanner.nextLine();

        if (user.login(inputUsername, inputPassword)) {
            user.changeEmail();
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }
    }
}