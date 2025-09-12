import java.security.MessageDigest;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class RegistrationForm {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "youruser";
    private static final String PASS = "yourpass";

    public static void main(String[] args) {
        String username = "testUser";
        String password = "testPassword123!";
        registerUser(username, password);
    }

    private static void registerUser(String username, String password) {
        try {
            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            storeUserInDatabase(username, salt, hashedPassword);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws Exception {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) throws Exception {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        return Base64.getEncoder().encodeToString(hashedPassword);
    }

    private static void storeUserInDatabase(String username, byte[] salt, String hashedPassword) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO users (username, salt, password) VALUES (?, ?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setBytes(2, salt);
            pstmt.setString(3, hashedPassword);
            pstmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}