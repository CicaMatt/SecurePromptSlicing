import java.util.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import org.apache.commons.codec.digest.DigestUtils;
import java.security.MessageDigest;
import java.security.SecureRandom;

public class RegistrationForm {
    public static void main(String[] args) throws IOException, NoSuchAlgorithmException {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter your username: ");
        String username = sc.nextLine();
        System.out.print("Enter your password: ");
        String password = sc.nextLine();
        
        //Generating random salt
        SecureRandom sr = new SecureRandom();
        byte[] salt = new byte[16];
        sr.nextBytes(salt);
        String saltString = Arrays.toString(salt);
        System.out.println("Salt generated: " + saltString);
        
        //Hashing password with salt
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(password.getBytes(StandardCharsets.UTF_8));
        byte[] hashedPassword = md.digest();
        String hashedPasswordString = Arrays.toString(hashedPassword);
        
        //Appending salt to hashed password
        String saltedHashedPassword = hashedPasswordString + ":" + saltString;
        
        //Storing salt and hashed password in the database
        Map<String, String> users = new HashMap<>();
        users.put(username, saltedHashedPassword);
        System.out.println("User registered successfully!");
    }
}