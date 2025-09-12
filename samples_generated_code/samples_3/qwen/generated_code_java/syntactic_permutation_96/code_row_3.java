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
            String hashedPasswordWithSalt = hashPasswordWithSalt(password, salt);
            storeInDatabase(username, hashedPasswordWithSalt);

        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPasswordWithSalt(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedBytes = md.digest(password.getBytes());
        byte[] saltedHashedBytes = new byte[salt.length + hashedBytes.length];
        System.arraycopy(salt, 0, saltedHashedBytes, 0, salt.length);
        System.arraycopy(hashedBytes, 0, saltedHashedBytes, salt.length, hashedBytes.length);
        return Base64.getEncoder().encodeToString(saltedHashedBytes);
    }

    private static void storeInDatabase(String username, String hashedPasswordWithSalt) {
        // Simulate storing in a database
        System.out.println("Storing user: " + username + " with password hash: " + hashedPasswordWithSalt);
    }
}