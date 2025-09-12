import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Scanner;

public class RegistrationForm {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter Username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter Password: ");
        String password = scanner.nextLine();
        
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedPassword = md.digest(password.getBytes());
            
            System.out.println("Registration successful!");
            System.out.println("Username: " + username);
            System.out.print("Hashed Password: ");
            for (byte b : hashedPassword) {
                System.out.printf("%02x", b);
            }
        } catch (NoSuchAlgorithmException e) {
            System.out.println("Error hashing password");
        }

        scanner.close();
    }
}