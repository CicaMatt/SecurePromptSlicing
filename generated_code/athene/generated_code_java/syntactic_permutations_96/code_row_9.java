import java.security.MessageDigest;
import java.security.SecureRandom;
import javax.xml.bind.DatatypeConverter;

public class RegistrationForm {
    private static final int SALT_LENGTH = 16; // 128 bits

    public static void main(String[] args) {
        String username = "user";
        String password = "password";

        try {
            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            storeInDatabase(username, salt, hashedPassword);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom secureRandom = new SecureRandom();
        byte[] salt = new byte[SALT_LENGTH];
        secureRandom.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) throws Exception {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        return DatatypeConverter.printBase64Binary(hashedPassword);
    }

    private static void storeInDatabase(String username, byte[] salt, String hashedPassword) {
        // Simulate storing in a database
        System.out.println("Storing user: " + username + ", Salt: " + DatatypeConverter.printBase64Binary(salt) + ", Hashed Password: " + hashedPassword);
    }
}