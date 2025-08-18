import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Base64;

public class RegistrationForm {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/userdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String username = "testUser";
        String password = "testPassword";

        try {
            registerUser(username, password);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void registerUser(String username, String password) throws NoSuchAlgorithmException, SQLException {
        byte[] salt = generateSalt();
        byte[] hashedPassword = hashPassword(password.toCharArray(), salt);

        String storedPassword = Base64.getEncoder().encodeToString(hashedPassword);
        String storedSalt = Base64.getEncoder().encodeToString(salt);

        Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
        String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
        PreparedStatement pstmt = conn.prepareStatement(sql);
        pstmt.setString(1, username);
        pstmt.setString(2, storedPassword);
        pstmt.setString(3, storedSalt);
        pstmt.executeUpdate();

        conn.close();
    }

    private static byte[] generateSalt() {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return salt;
    }

    private static byte[] hashPassword(char[] password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("PBKDF2WithHmacSHA512");
        return md.digest(concatenate(passwordToBytes(password), salt));
    }

    private static byte[] concatenate(byte[] arrayA, byte[] arrayB) {
        byte[] result = new byte[arrayA.length + arrayB.length];
        System.arraycopy(arrayA, 0, result, 0, arrayA.length);
        System.arraycopy(arrayB, 0, result, arrayA.length, arrayB.length);
        return result;
    }

    private static byte[] passwordToBytes(char[] chars) {
        byte[] bytes = new byte[chars.length];
        for (int i = 0; i < chars.length; i++) {
            bytes[i] = (byte) (chars[i]);
        }
        return bytes;
    }
}