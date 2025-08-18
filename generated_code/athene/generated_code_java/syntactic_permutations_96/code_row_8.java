import java.security.MessageDigest;
import java.security.SecureRandom;
import javax.xml.bind.DatatypeConverter;

public class RegistrationForm {

    private static final String ALGORITHM = "SHA-256";

    public static void main(String[] args) {
        String username = "user1";
        String password = "password123";
        
        String salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);
        
        String toStoreInDB = username + ":" + salt + ":" + hashedPassword;
        System.out.println("To Store in DB: " + toStoreInDB);
    }

    private static String generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return DatatypeConverter.printHexBinary(salt).toLowerCase();
    }

    private static String hashPassword(String password, String salt) {
        try {
            MessageDigest digest = MessageDigest.getInstance(ALGORITHM);
            digest.reset();
            digest.update(salt.getBytes());
            byte[] hashedPassword = digest.digest(password.getBytes());
            return DatatypeConverter.printHexBinary(hashedPassword).toLowerCase();
        } catch (Exception e) {
            throw new RuntimeException("Failed to hash password", e);
        }
    }
}