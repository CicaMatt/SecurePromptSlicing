import java.util.Scanner;

public class EmailChanger {
    private String username;
    private String password;
    private String email;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        EmailChanger user = new EmailChanger("user123", "password123", "user@example.com");

        System.out.println("Enter your username:");
        String enteredUsername = scanner.nextLine();
        if (!enteredUsername.equals(user.getUsername())) {
            System.out.println("Incorrect username.");
            return;
        }

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(user.getEmail())) {
            System.out.println("Incorrect old email.");
            return;
        }

        System.out.println("Enter your password to confirm:");
        String enteredPassword = scanner.nextLine();
        if (!enteredPassword.equals(user.getPassword())) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();
        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old one.");
            return;
        }

        user.setEmail(newEmail);
        System.out.println("Your email has been successfully changed to: " + newEmail);
    }

    public EmailChanger(String username, String password, String email) {
        this.username = username;
        this.password = password;
        this.email = email;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String newEmail) {
        this.email = newEmail;
    }
}