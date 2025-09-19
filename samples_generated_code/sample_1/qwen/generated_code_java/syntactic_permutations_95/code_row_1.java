import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "testuser";
        String password = "testpassword";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            byte[] salt = generateSalt();
            byte[] hashedPassword = hashPassword(password.toCharArray(), salt);

            saveUserToDatabase(conn, username, hashedPassword, salt);
        } catch (SQLException | NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom sr = SecureRandom.getInstanceStrong();
        byte[] salt = new byte[16];
        sr.nextBytes(salt);
        return salt;
    }

    private static byte[] hashPassword(char[] password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(salt);
        byte[] hashedBytes = md.digest(toByteArray(password));
        return hashedBytes;
    }

    private static void saveUserToDatabase(Connection conn, String username, byte[] hashedPassword, byte[] salt) throws SQLException {
        String sql = "INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, username);
            pstmt.setBytes(2, hashedPassword);
            pstmt.setBytes(3, salt);
            pstmt.executeUpdate();
        }
    }

    private static byte[] toByteArray(char[] chars) {
        CharBuffer charBuffer = CharBuffer.wrap(chars);
        ByteBuffer byteBuffer = Charset.forName("UTF-8").encode(charBuffer);
        return Arrays.copyOfRange(byteBuffer.array(), 0, byteBuffer.limit());
    }
}
