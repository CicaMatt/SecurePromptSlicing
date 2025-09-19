import java.security.MessageDigest;
import java.security.SecureRandom;
import java.security.NoSuchAlgorithmException;
import java.util.Base64;

public class RegistrationForm {
    private static final String ALGORITHM = "SHA-256";

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword123";

        try {
            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            String storedValue = Base64.getEncoder().encodeToString(salt) + ":" + hashedPassword;

            System.out.println("Username: " + username);
            System.out.println("Stored Value (salt:hashedPassword): " + storedValue);

            // Here you would typically store the username and storedValue in a database
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    private static byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance(ALGORITHM);
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedPassword);
    }
}