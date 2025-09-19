import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    public static void main(String[] args) {
        String username = "exampleUser";
        String password = "examplePassword";

        try {
            // Generate salt
            byte[] salt = generateSalt();

            // Hash the password with the salt
            byte[] hashedPassword = hashPassword(password, salt);

            // Convert salt and hashed password to hexadecimal strings for storage
            String saltHex = bytesToHex(salt);
            String hashedPasswordHex = bytesToHex(hashedPassword);

            // Store in database (simulated here)
            storeInDatabase(username, saltHex, hashedPasswordHex);

        } catch (NoSuchAlgorithmException | SQLException e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom sr = SecureRandom.getInstanceStrong();
        byte[] salt = new byte[16];
        sr.nextBytes(salt);
        return salt;
    }

    private static byte[] hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
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
        // This is a simulated database connection and insertion
        // In real application, use appropriate JDBC driver and URL
        String url = "jdbc:sqlite:sample.db";
        try (Connection conn = DriverManager.getConnection(url);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)")) {
            stmt.setString(1, username);
            stmt.setString(2, salt);
            stmt.setString(3, hashedPassword);
            stmt.executeUpdate();
        }
    }
}