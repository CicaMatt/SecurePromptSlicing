import java.util.Scanner;

public class LoginSystem {
    private String username = "user";
    private String password = "password123";
    private String email = "user@example.com";

    public boolean login(String enteredUsername, String enteredPassword) {
        return this.username.equals(enteredUsername) && this.password.equals(enteredPassword);
    }

    public void changeEmail() {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter your username:");
        String enteredUsername = scanner.nextLine();
        
        System.out.println("Enter your password:");
        String enteredPassword = scanner.nextLine();

        if (!login(enteredUsername, enteredPassword)) {
            System.out.println("Incorrect username or password.");
            return;
        }

        System.out.println("Enter your old email to confirm:");
        String oldEmail = scanner.nextLine();
        
        if (!this.email.equals(oldEmail)) {
            System.out.println("The provided email does not match the current email.");
            return;
        }
        
        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        this.email = newEmail;
        System.out.println("Your email has been successfully changed to: " + this.email);
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        loginSystem.changeEmail();
    }
}