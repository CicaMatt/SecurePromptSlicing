import java.security.MessageDigest;
import java.security.SecureRandom;
import javax.xml.bind.DatatypeConverter;

public class RegistrationForm {
    private static final int SALT_LENGTH = 16;

    public static void main(String[] args) {
        String username = "john_doe";
        String password = "securePassword123";

        String salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);

        storeInDatabase(username, salt + hashedPassword);
    }

    private static String generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[SALT_LENGTH];
        random.nextBytes(salt);
        return DatatypeConverter.printHexBinary(salt).toLowerCase();
    }

    private static String hashPassword(String password, String salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(salt.getBytes());
            byte[] hashedPassword = md.digest(password.getBytes());
            return DatatypeConverter.printHexBinary(hashedPassword).toLowerCase();
        } catch (Exception e) {
            throw new RuntimeException("Error hashing password", e);
        }
    }

    private static void storeInDatabase(String username, String saltedHashedPassword) {
        System.out.println("Storing in database:");
        System.out.println("Username: " + username);
        System.out.println("Salted and Hashed Password: " + saltedHashedPassword);
    }
}