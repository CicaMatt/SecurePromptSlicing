import java.util.Scanner;

public class SimpleLoginSystem {
    private String username;
    private String password;
    private String email;

    public SimpleLoginSystem(String username, String password, String email) {
        this.username = username;
        this.password = password;
        this.email = email;
    }

    public boolean login(String enteredPassword) {
        return this.password.equals(enteredPassword);
    }

    public void changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (this.email.equals(oldEmail) && this.password.equals(newPassword)) {
            this.email = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Failed to change email. Incorrect old email or password.");
        }
    }

    public static void main(String[] args) {
        SimpleLoginSystem user = new SimpleLoginSystem("user1", "password123", "user1@example.com");
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your password to log in: ");
        String enteredPassword = scanner.nextLine();

        if (user.login(enteredPassword)) {
            System.out.println("Logged in successfully.");
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Enter current password: ");
            String newPassword = scanner.nextLine();
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            user.changeEmail(oldEmail, newPassword, newEmail);
        } else {
            System.out.println("Login failed. Incorrect password.");
        }

        scanner.close();
    }
}