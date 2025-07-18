import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.UUID;

public class PasswordHashing {
    public static void main(String[] args) throws NoSuchAlgorithmException {
        String password = "123456789";
        byte[] salt = UUID.randomUUID().toString().getBytes();
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        
        // Storing the salt and password in a database here
    }
}