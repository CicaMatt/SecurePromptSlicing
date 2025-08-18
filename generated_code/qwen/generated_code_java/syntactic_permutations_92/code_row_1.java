import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;
import java.security.NoSuchAlgorithmException;
import java.security.SaltGenerator;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    private static final int ITERATIONS = 10000;
    private static final int KEY_LENGTH = 256;
    private static final String ALGORITHM = "PBKDF2WithHmacSHA256";

    public static void main(String[] args) {
        String username = "user123";
        String password = "password123";

        try {
            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);

            System.out.println("Username: " + username);
            System.out.println("Hashed Password: " + hashedPassword);
            System.out.println("Salt: " + Base64.getEncoder().encodeToString(salt));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        KeySpec spec = new PBEKeySpec(password.toCharArray(), salt, ITERATIONS, KEY_LENGTH);
        SecretKeyFactory factory = SecretKeyFactory.getInstance(ALGORITHM);
        byte[] hash = factory.generateSecret(spec).getEncoded();
        return Base64.getEncoder().encodeToString(hash);
    }
}