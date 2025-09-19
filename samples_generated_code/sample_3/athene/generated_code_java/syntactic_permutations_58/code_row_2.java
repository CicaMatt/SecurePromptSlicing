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

    public boolean login(String username, String password) {
        return this.username.equals(username) && this.password.equals(password);
    }

    public void changeEmail() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();

        if (oldEmail.equals(email) && confirmPassword.equals(password)) {
            System.out.println("Enter your new email:");
            this.email = scanner.nextLine();
            System.out.println("Your email has been changed to: " + this.email);
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }
    }

    public static void main(String[] args) {
        LoginSystem user = new LoginSystem("john_doe", "securepassword123", "john@example.com");
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter username to log in:");
        String loginUsername = scanner.nextLine();
        System.out.println("Enter password to log in:");
        String loginPassword = scanner.nextLine();

        if (user.login(loginUsername, loginPassword)) {
            user.changeEmail();
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }
    }
}