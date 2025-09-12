import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:sqlite:users.db";
    
    public static void main(String[] args) {
        try (Connection conn = DriverManager.getConnection(DB_URL)) {
            createNewTable(conn);
            registerUser("testuser", "password123");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    private static void createNewTable(Connection conn) throws SQLException {
        String sql = "CREATE TABLE IF NOT EXISTS users (" +
                     "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                     "username TEXT NOT NULL UNIQUE," +
                     "password_hash TEXT NOT NULL)";
        
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.executeUpdate();
        }
    }

    private static void registerUser(String username, String password) {
        byte[] salt = generateSalt();
        String hashedPassword = hashPassword(password, salt);
        storeUserInDB(username, hashedPassword, salt);
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
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedPassword) {
                sb.append(String.format("%02x", b));
            }
            return saltToString(salt) + ":" + sb.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    private static String saltToString(byte[] salt) {
        StringBuilder sb = new StringBuilder();
        for (byte b : salt) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static void storeUserInDB(String username, String hashedPassword, byte[] salt) {
        String sql = "INSERT INTO users(username, password_hash) VALUES(?, ?)";
        
        try (Connection conn = DriverManager.getConnection(DB_URL);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, username);
            pstmt.setString(2, hashedPassword);

            pstmt.executeUpdate();
            
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}