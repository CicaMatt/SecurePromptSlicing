import java.security.*;
import java.sql.*;
import javax.crypto.spec.SecretKeySpec;
public class PasswordHash {
    public static String generateHash(String password) throws Exception {
        byte[] salt = new byte[16];
        SecureRandom secureRandom = SecureRandom.getInstance("SHA1PRNG");
        secureRandom.nextBytes(salt);
        MessageDigest messageDigest = MessageDigest.getInstance("SHA-512");
        messageDigest.update(salt);
        byte[] hashedPassword = messageDigest.digest(password.getBytes("UTF-8"));
        return new String(hashedPassword);
    }
}