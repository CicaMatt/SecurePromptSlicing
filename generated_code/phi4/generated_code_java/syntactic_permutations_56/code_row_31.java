import java.util.Scanner;

public class SimpleLogin {
    private static String userEmail = "user@example.com";
    private static String userPassword = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter email: ");
        String inputEmail = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String inputPassword = scanner.nextLine();

        if (login(inputEmail, inputPassword)) {
            changeEmail(scanner);
        } else {
            System.out.println("Invalid login credentials.");
        }

        scanner.close();
    }
    
    private static boolean login(String email, String password) {
        return userEmail.equals(email) && userPassword.equals(password);
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(userEmail)) {
            System.out.println("Old email does not match.");
            return;
        }
        
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        
        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!userPassword.equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }
        
        userEmail = newEmail;
        System.out.println("Email changed successfully to " + userEmail);
    }
}