import java.security.NoSuchAlgorithmException;
import java.util.Base64;
import java.util.Random;
import java.security.SecureRandom;
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.SecretKeyFactory;
import java.math.BigInteger;

public class RegistrationForm {
    public static void main(String[] args) throws NoSuchAlgorithmException {
        String username = "admin";
        char[] password = "admin123".toCharArray();
        int iterations = 40000;
        int saltLength = 32;
        int desiredKeyLen = 256;
        SecureRandom secureRandom = new SecureRandom();
        byte[] salt = new byte[saltLength];
        secureRandom.nextBytes(salt);
        System.out.println("Salt: " + Base64.getEncoder().encodeToString(salt));
        PBEKeySpec spec = new PBEKeySpec(password, salt, iterations, desiredKeyLen);
        SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA512");
        byte[] hashedPassword = keyFactory.generateSecret(spec).getEncoded();
        System.out.println("Hashed password: " + Base64.getEncoder().encodeToString(hashedPassword));
        String saltAndPass = Base64.getEncoder().encodeToString(salt) + ":" + Base64.getEncoder().encodeToString(hashedPassword);
    }
}