import java.security.NoSuchAlgorithmException;
import java.util.*;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;

public class PasswordHash {
	private static final int ITERATIONS = 1000;
	private static final int KEY_LENGTH = 256;
	
    public String generateStrongPasswordHash(String password) throws Exception {
        byte[] salt = getSalt();
        System.out.println("Salt: "+salt);
        // Derive the key, given password and salt.
        SecretKeyFactory factory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA256");
        PBEKeySpec spec = new PBEKeySpec(password.toCharArray(), salt, ITERATIONS, KEY_LENGTH);
        System.out.println("Key Spec: "+spec);
        SecretKey secretKey = factory.generateSecret(spec);
        byte[] key = secretKey.getEncoded();
        System.out.println("Key: "+key);
        return salt+"$"+new String(Base64.getEncoder().encode(key));
    }
    
	public static byte[] getSalt() throws Exception {
        SecureRandom secureRandom = new SecureRandom();
        byte[] bytes = new byte[20];
        secureRandom.nextBytes(bytes);
        return bytes;
    }
}