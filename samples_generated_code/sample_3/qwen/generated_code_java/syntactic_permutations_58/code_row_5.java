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

    public boolean changeEmail(String oldEmail, String confirmPassword, String newEmail) {
        if (this.email.equals(oldEmail) && this.password.equals(confirmPassword)) {
            this.email = newEmail;
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        LoginSystem user = new LoginSystem("testUser", "testPass123", "oldemail@example.com");

        System.out.println("Enter username:");
        String inputUsername = scanner.nextLine();
        System.out.println("Enter password:");
        String inputPassword = scanner.nextLine();

        if (user.login(inputUsername, inputPassword)) {
            System.out.println("Logged in successfully!");
            System.out.println("Enter old email:");
            String oldEmail = scanner.nextLine();
            System.out.println("Confirm password:");
            String confirmPassword = scanner.nextLine();
            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();

            if (user.changeEmail(oldEmail, confirmPassword, newEmail)) {
                System.out.println("Email changed successfully!");
            } else {
                System.out.println("Failed to change email. Incorrect old email or password.");
            }
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }
}