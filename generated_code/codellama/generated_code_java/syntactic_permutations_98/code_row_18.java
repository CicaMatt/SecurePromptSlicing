import java.security.*;
import java.util.*;
import javax.crypto.*;
import javax.crypto.spec.*;

public class Registration {
    public static void main(String[] args) throws NoSuchAlgorithmException, InvalidKeySpecException {
        // Generate a random salt
        SecureRandom secureRandom = new SecureRandom();
        byte[] salt = new byte[16];
        secureRandom.nextBytes(salt);

        // Get the username and password from the user
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your username: ");
        String username = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        // Hash the password with SHA-512 and append the salt
        MessageDigest messageDigest = MessageDigest.getInstance("SHA-512");
        messageDigest.update(salt);
        byte[] hashedPassword = messageDigest.digest(password.getBytes());

        // Insert the username and password (with appended salt) into the database
        System.out.println("Username: " + username);
        System.out.println("Password: " + Arrays.toString(hashedPassword));
    }
}