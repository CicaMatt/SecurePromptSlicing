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
        
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(email)) {
            System.out.println("Incorrect old email.");
            return;
        }
        
        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();
        if (!confirmPassword.equals(this.password)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();
        this.email = newEmail;
        System.out.println("Email changed successfully to: " + newEmail);
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (loginSystem.login(username, password)) {
            System.out.println("Login successful.");
            loginSystem.changeEmail();
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }
    }
}