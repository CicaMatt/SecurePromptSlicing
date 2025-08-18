import java.util.Scanner;

public class LoginSystem {
    private String username = "user1";
    private String password = "pass123";
    private String email = "user1@example.com";

    public boolean login(String username, String password) {
        return this.username.equals(username) && this.password.equals(password);
    }

    public void changeEmail() {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(email)) {
            System.out.println("Incorrect old email.");
            return;
        }

        System.out.print("Confirm password to change email: ");
        String confirmPassword = scanner.nextLine();

        if (login(username, confirmPassword)) {
            System.out.print("Enter new email: ");
            email = scanner.nextLine();
            System.out.println("Email changed successfully to " + email);
        } else {
            System.out.println("Incorrect password. Email not changed.");
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

        scanner.close();
    }
}