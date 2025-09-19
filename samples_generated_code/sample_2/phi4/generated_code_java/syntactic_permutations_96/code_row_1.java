import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.xml.bind.DatatypeConverter;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        // Example usage
        registerUser("exampleUsername", "examplePassword");
    }

    public static void registerUser(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            storeInDatabase(conn, username, hashedPassword + ":" + salt);

            System.out.println("User registered successfully!");
        } catch (SQLException | NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    private static String generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] saltBytes = new byte[16];
        random.nextBytes(saltBytes);
        return DatatypeConverter.printHexBinary(saltBytes);
    }

    private static String hashPassword(String password, String salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update((salt + password).getBytes());
        byte[] hashedBytes = md.digest();
        return DatatypeConverter.printHexBinary(hashedBytes);
    }

    private static void storeInDatabase(Connection conn, String username, String credentials) throws SQLException {
        String sql = "INSERT INTO users (username, credentials) VALUES (?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, username);
            pstmt.setString(2, credentials);
            pstmt.executeUpdate();
        }
    }
}
