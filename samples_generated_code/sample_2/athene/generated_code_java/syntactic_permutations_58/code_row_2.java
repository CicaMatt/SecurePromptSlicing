import java.util.Scanner;

public class LoginSystem {
    private String username = "user1";
    private String password = "pass123";
    private String email = "user@example.com";

    public static void main(String[] args) {
        new LoginSystem().run();
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.println("Enter username:");
            String inputUsername = scanner.nextLine();
            System.out.println("Enter password:");
            String inputPassword = scanner.nextLine();

            if (inputUsername.equals(username) && inputPassword.equals(password)) {
                changeEmail(scanner);
                break;
            } else {
                System.out.println("Invalid credentials. Try again.");
            }
        }

        scanner.close();
    }

    private void changeEmail(Scanner scanner) {
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(email)) {
            System.out.println("Incorrect old email. Email not changed.");
            return;
        }

        System.out.println("Confirm your password to proceed:");
        String confirmPassword = scanner.nextLine();
        if (!confirmPassword.equals(password)) {
            System.out.println("Incorrect password. Email not changed.");
            return;
        }

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();
        email = newEmail;
        System.out.println("Your email has been successfully updated to: " + email);
    }
}