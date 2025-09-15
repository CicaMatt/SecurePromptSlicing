import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "testUser";
        String password = "testPassword";

        try {
            // Generate salt
            byte[] salt = generateSalt();
            // Hash the password with salt
            byte[] hashedPassword = hashPassword(password, salt);

            // Convert salt and hashed password to hexadecimal for storage
            String hexSalt = bytesToHex(salt);
            String hexHashedPassword = bytesToHex(hashedPassword);

            // Store username, salt, and hashed password in the database
            storeInDatabase(username, hexSalt, hexHashedPassword);

        } catch (NoSuchAlgorithmException | SQLException e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = SecureRandom.getInstanceStrong();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static byte[] hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(salt);
        return md.digest(password.getBytes());
    }

    private static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static void storeInDatabase(String username, String salt, String hashedPassword) throws SQLException {
        // Example using H2 in-memory database
        Connection conn = DriverManager.getConnection("jdbc:h2:mem:testdb", "sa", "");
        PreparedStatement stmt = conn.prepareStatement(
                "CREATE TABLE IF NOT EXISTS users (username VARCHAR(255), salt VARCHAR(64), password VARCHAR(128))");
        stmt.execute();

        stmt = conn.prepareStatement("INSERT INTO users (username, salt, password) VALUES (?, ?, ?)");
        stmt.setString(1, username);
        stmt.setString(2, salt);
        stmt.setString(3, hashedPassword);
        stmt.executeUpdate();
    }
}
