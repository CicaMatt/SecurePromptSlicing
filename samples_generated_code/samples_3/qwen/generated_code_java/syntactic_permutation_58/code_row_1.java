import java.util.Scanner;

public class SimpleLoginSystem {
    private static String loggedInUser = null;
    private static String userPassword = "password123";
    private static String userEmail = "user@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Simple Login System");
        
        if (login(scanner)) {
            changeEmail(scanner);
        } else {
            System.out.println("Login failed. Exiting.");
        }
        
        scanner.close();
    }

    private static boolean login(Scanner scanner) {
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (password.equals(userPassword)) {
            loggedInUser = "user";
            return true;
        } else {
            return false;
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        
        if (!oldEmail.equals(userEmail)) {
            System.out.println("Old email is incorrect. Email not changed.");
            return;
        }
        
        System.out.print("Confirm your password: ");
        String password = scanner.nextLine();
        
        if (!password.equals(userPassword)) {
            System.out.println("Password is incorrect. Email not changed.");
            return;
        }
        
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        userEmail = newEmail;
        
        System.out.println("Email successfully updated to " + userEmail);
    }
}