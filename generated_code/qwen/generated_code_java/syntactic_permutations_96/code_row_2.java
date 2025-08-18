import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword";

        try {
            byte[] salt = generateSalt();
            String hashedPasswordWithSalt = hashPassword(password, salt);

            // Here you would store the username and hashedPasswordWithSalt in your database
            System.out.println("Username: " + username);
            System.out.println("Hashed Password with Salt: " + hashedPasswordWithSalt);

        } catch (NoSuchAlgorithmException e) {
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
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedBytes = md.digest(password.getBytes());
        byte[] hashedBytesWithSalt = new byte[salt.length + hashedBytes.length];
        System.arraycopy(salt, 0, hashedBytesWithSalt, 0, salt.length);
        System.arraycopy(hashedBytes, 0, hashedBytesWithSalt, salt.length, hashedBytes.length);
        return Base64.getEncoder().encodeToString(hashedBytesWithSalt);
    }
}