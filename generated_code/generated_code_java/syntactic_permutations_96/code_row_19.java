import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegistrationForm {
    public static void main(String[] args) throws NoSuchAlgorithmException {
        String username = "admin";
        String password = "password123!";
        byte[] salt = new byte[16]; // 16-byte salt

        // Generate the hash and salt
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());

        // Print the hashed password
        System.out.println(hashedPassword);
    }
}