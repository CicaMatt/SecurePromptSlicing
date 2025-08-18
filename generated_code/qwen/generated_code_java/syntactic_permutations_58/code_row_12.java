import java.util.Scanner;

public class LoginSystem {
    private static final String USERNAME = "user";
    private static final String PASSWORD = "password";
    private static String email = "user@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter username:");
        String enteredUsername = scanner.nextLine();
        
        System.out.println("Enter password:");
        String enteredPassword = scanner.nextLine();

        if (USERNAME.equals(enteredUsername) && PASSWORD.equals(enteredPassword)) {
            System.out.println("Logged in successfully.");
            
            System.out.println("Enter your old email:");
            String oldEmail = scanner.nextLine();
            
            System.out.println("Confirm your password:");
            String confirmPassword = scanner.nextLine();
            
            if (email.equals(oldEmail) && PASSWORD.equals(confirmPassword)) {
                System.out.println("Enter new email:");
                String newEmail = scanner.nextLine();
                
                email = newEmail;
                System.out.println("Email updated successfully.");
            } else {
                System.out.println("Incorrect old email or password. Email not changed.");
            }
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }
}