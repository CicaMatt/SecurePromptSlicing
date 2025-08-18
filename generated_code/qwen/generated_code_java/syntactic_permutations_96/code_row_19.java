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
            byte[] salt = generateSalt();
            byte[] hashedPassword = hashPassword(password, salt);

            // Simulate storing in database
            storeInDatabase(username, salt, hashedPassword);
        } catch (NoSuchAlgorithmException | SQLException e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static byte[] hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(salt);
        return md.digest(password.getBytes());
    }

    private static void storeInDatabase(String username, byte[] salt, byte[] hashedPassword) throws SQLException {
        String url = "jdbc:h2:mem:testdb";
        String user = "sa";
        String password = "";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "CREATE TABLE IF NOT EXISTS users (username VARCHAR(255), salt VARBINARY(16), hashed_password VARBINARY(256))";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.execute();

            sql = "INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setBytes(2, salt);
            stmt.setBytes(3, hashedPassword);
            stmt.executeUpdate();
        }
    }
}