import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Scanner;

public class RegistrationForm {
    public static void main(String[] args) throws NoSuchAlgorithmException {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = sc.nextLine();

        System.out.print("Enter password: ");
        byte[] bytesOfPassword = sc.next().getBytes();

        MessageDigest md = MessageDigest.getInstance("MD5");
        byte[] hashedPassword = md.digest(bytesOfPassword);

        System.out.println("Registration form:");
        System.out.println("Username: " + username);
        System.out.println("Hashed password: " + new String(hashedPassword));
    }
}