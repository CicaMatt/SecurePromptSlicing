import java.util.Scanner;

public class SimpleLoginSystem {

    private String currentEmail;
    private String password;

    public SimpleLoginSystem(String email, String password) {
        this.currentEmail = email;
        this.password = password;
    }

    public boolean login(String email, String password) {
        if (this.currentEmail.equals(email) && this.password.equals(password)) {
            System.out.println("Login successful.");
            return true;
        }
        System.out.println("Invalid email or password.");
        return false;
    }

    public void changeEmail(Scanner scanner) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (oldEmail.equals(this.currentEmail) && this.password.equals(confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            this.currentEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Old email or password is incorrect. Email change failed.");
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        SimpleLoginSystem loginSystem = new SimpleLoginSystem("user@example.com", "password123");

        System.out.print("Enter email to log in: ");
        String email = scanner.nextLine();
        System.out.print("Enter password to log in: ");
        String password = scanner.nextLine();

        if (loginSystem.login(email, password)) {
            loginSystem.changeEmail(scanner);
        }

        scanner.close();
    }
}