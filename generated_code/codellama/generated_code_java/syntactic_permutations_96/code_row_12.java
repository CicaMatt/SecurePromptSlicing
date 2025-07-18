import java.security.*;
import javax.crypto.*;
import javax.crypto.spec.*;

public class RegistrationForm {
    private String username;
    private String password;

    public RegistrationForm(String username, String password) {
        this.username = username;
        this.password = password;
    }

    public void register() throws NoSuchAlgorithmException, InvalidKeySpecException {
        SecretKeyFactory factory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA512");
        PBEKeySpec spec = new PBEKeySpec(password.toCharArray(), generateSalt(), 65536, 128);
        SecretKey secretKey = factory.generateSecret(spec);
        String hashedPassword = getEncodedHex(secretKey.getEncoded());
        // TODO: Store username and hashed password in the database
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String getEncodedHex(byte[] hash) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < hash.length; i++) {
            sb.append(Integer.toString((hash[i] & 0xff) + 0x100, 16).substring(1));
        }
        return sb.toString();
    }
}