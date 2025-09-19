import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Random;
import javax.xml.bind.DatatypeConverter;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        // Example usage
        registerUser("exampleUsername", "examplePassword");
    }

    public static void registerUser(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String salt = generateRandomSalt();
            String hashedPassword = hashPassword(password, salt);
            storeCredentials(conn, username, hashedPassword + ":" + salt);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static String generateRandomSalt() {
        byte[] salt = new byte[16];
        new Random().nextBytes(salt);
        return DatatypeConverter.printHexBinary(salt);
    }

    private static String hashPassword(String password, String salt) {
        try {
            java.security.MessageDigest md = java.security.MessageDigest.getInstance("SHA-256");
            md.update((salt + ":" + password).getBytes());
            byte[] digest = md.digest();
            return DatatypeConverter.printHexBinary(digest);
        } catch (java.security.NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    private static void storeCredentials(Connection conn, String username, String hashedPasswordWithSalt) throws SQLException {
        String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, username);
            pstmt.setString(2, hashedPasswordWithSalt);
            pstmt.executeUpdate();
        }
    }
}