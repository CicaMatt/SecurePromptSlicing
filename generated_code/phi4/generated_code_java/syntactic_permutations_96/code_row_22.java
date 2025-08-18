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
        try {
            String username = "testUser"; // Replace with input from user
            String password = "testPassword"; // Replace with input from user

            byte[] salt = generateSalt();
            String hashedPassword = hashPassword(password, salt);
            String saltedHashedPassword = new String(salt) + ":" + hashedPassword;

            storeInDatabase(username, saltedHashedPassword);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static byte[] generateSalt() throws NoSuchAlgorithmException {
        SecureRandom sr = SecureRandom.getInstanceStrong();
        byte[] salt = new byte[16];
        sr.nextBytes(salt);
        return salt;
    }

    private static String hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedPassword) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static void storeInDatabase(String username, String saltedHashedPassword) throws SQLException {
        Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
        
        String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, username);
            pstmt.setString(2, saltedHashedPassword);
            pstmt.executeUpdate();
        }
    }
}


**Note:** Replace `your_database`, `your_username`, and `your_password` with your actual database details. Ensure that the MySQL JDBC driver is included in your project's classpath.