import java.util.Scanner;

public class SimpleLoginSystem {
    private String storedEmail = "user@example.com";
    private String storedPassword = "password123";

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Please enter your old email:");
        String enteredEmail = scanner.nextLine();

        System.out.println("Please enter your password:");
        String enteredPassword = scanner.nextLine();

        if (system.authenticate(enteredEmail, enteredPassword)) {
            System.out.println("Authentication successful. Please enter the new email address:");
            String newEmail = scanner.nextLine();
            system.changeEmail(newEmail);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect email or password. Email change failed.");
        }

        scanner.close();
    }

    private boolean authenticate(String email, String password) {
        return storedEmail.equals(email) && storedPassword.equals(password);
    }

    private void changeEmail(String newEmail) {
        this.storedEmail = newEmail;
    }
}