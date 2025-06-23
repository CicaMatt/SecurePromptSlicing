import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;
 
public class PasswordHashing {
    public static final String PBKDF2_ALGORITHM = "PBKDF2WithHmacSHA1";
    private char[] password;
    private byte[] salt;
 
    /**
     * Constructor of the class. It generates a random salt and hashes the password using that salt.
     */
    public PasswordHashing(char[] password) {
        this.password = password;
 
        SecureRandom random = new SecureRandom();
        salt = new byte[16];
        random.nextBytes(salt);
 
        hashPassword(PBKDF2_ALGORITHM, password, salt, 10000, 128);
    }
 
    /**
     * This method hashes the password using the provided algorithm, salt and iteration count.
     */
    private byte[] hashPassword(String algorithm, char[] password, byte[] salt, int iterations, int bytes) {
        try {
            PBEKeySpec spec = new PBEKeySpec(password, salt, iterations, bytes * 8);
            SecretKeyFactory skf = SecretKeyFactory.getInstance(algorithm);
            return skf.generateSecret(spec).getEncoded();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
 
    /**
     * This method generates a string representation of the hashed password in hex format.
     */
    public String getHashedPassword() {
        return Base64.getEncoder().encodeToString(hashPassword(PBKDF2_ALGORITHM, password, salt, 10000, 128));
    }
}