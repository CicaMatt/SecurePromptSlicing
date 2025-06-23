import javax.crypto.spec.SecretKeySpec;
import java.security.MessageDigest;
import java.util.Base64;

class PasswordManager {
    private static final String HASH_ALGORITHM = "SHA-512";
    private static final int SALT_LENGTH = 32;
    private static final String ENCODING = "UTF-8";

    public static void main(String[] args) {
        // Generate salt
        byte[] saltBytes = generateSalt();
        String salt = new String(saltBytes, Base64.getEncoder());

        // Get password from user input
        String username = "username";
        char[] password = {'p', 'a', 's', 's', 'w', 'o', 'r', 'd'};

        byte[] hashedPasswordBytes = getHashedPassword(password, saltBytes);
        String hashedPassword = new String(hashedPasswordBytes, Base64.getEncoder());

        // Store the username and hashed password in database
    }

    private static byte[] generateSalt() {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-512");
            return md.digest(String.valueOf(System.currentTimeMillis()).getBytes());
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    private static byte[] getHashedPassword(char[] password, byte[] saltBytes) {
        try {
            SecretKeySpec key = new SecretKeySpec(saltBytes, HASH_ALGORITHM);
            MessageDigest md = MessageDigest.getInstance("SHA-512");
            md.reset();
            md.update(String.valueOf(password).getBytes());
            return md.digest();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}