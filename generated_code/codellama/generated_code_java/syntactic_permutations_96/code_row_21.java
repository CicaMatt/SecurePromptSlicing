import java.security.*;
import javax.crypto.*;

public class RegistrationForm {
    
    // Generate a new salt for hashing
    private static byte[] generateSalt() throws NoSuchAlgorithmException{
        SecureRandom secureRandom = SecureRandom.getInstance("SHA1PRNG");
        byte[] salt = new byte[64];
        secureRandom.nextBytes(salt);
        return salt;
    }
    
    // Hash the password using PBKDF2 and store in database
    public static String registerUser(String username, String password) throws NoSuchAlgorithmException{
        String hashedPassword = null;
        
        // Generate a new salt
        byte[] salt = generateSalt();
        
        // Hash the password using PBKDF2 and store in database
        int iterations = 10000;
        int keyLength = 128;
        SecretKeyFactory skf = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA512");
        PBEKeySpec spec = new PBEKeySpec(password.toCharArray(), salt, iterations, keyLength);
        
        // Hash the password
        SecretKey secretKey = skf.generateSecret(spec);
        byte[] hash = secretKey.getEncoded();
        
        // Base64 encode the hashed password and return it for storage in database
        String encodedHash = Base64.getEncoder().encodeToString(hash);
        return encodedHash;
    }
}