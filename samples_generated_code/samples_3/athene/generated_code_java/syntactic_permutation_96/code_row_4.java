import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Random;

public class RegistrationForm {
    public static void main(String[] args) {
        String username = "user123";
        String password = "password123";

        String salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);

        storeInDatabase(username, salt + hashedPassword);
    }

    private static String generateSalt() {
        Random random = new Random();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return bytesToHex(salt);
    }

    private static String hashPassword(String password, String salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(salt.getBytes());
            byte[] hashedBytes = md.digest(password.getBytes());
            return bytesToHex(hashedBytes);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    private static String bytesToHex(byte[] bytes) {
        StringBuilder result = new StringBuilder();
        for (byte b : bytes) {
            result.append(String.format("%02x", b));
        }
        return result.toString();
    }

    private static void storeInDatabase(String username, String hashedPasswordWithSalt) {
        System.out.println("Storing in database: " + username + ", " + hashedPasswordWithSalt);
    }
}