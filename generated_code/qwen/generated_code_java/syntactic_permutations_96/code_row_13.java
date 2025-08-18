import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "testUser";
        String password = "testPassword";

        // Generate a salt
        byte[] salt = generateSalt();

        // Hash the password with the salt
        String hashedPasswordWithSalt = hashPassword(password, salt);

        // Store the username and hashed password with salt in the database
        storeInDatabase(username, hashedPasswordWithSalt, salt);
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(salt);
            byte[] hashedPassword = md.digest(password.getBytes());
            // Convert bytes to hex format
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedPassword) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    private static void storeInDatabase(String username, String hashedPasswordWithSalt, byte[] salt) {
        // This is a placeholder for database storage logic
        // In a real application, you would use JDBC or an ORM to store the data
        System.out.println("Storing in database:");
        System.out.println("Username: " + username);
        System.out.println("Hashed Password with Salt: " + hashedPasswordWithSalt);
        System.out.print("Salt: ");
        for (byte b : salt) {
            System.out.printf("%02x", b);
        }
        System.out.println();
    }
}