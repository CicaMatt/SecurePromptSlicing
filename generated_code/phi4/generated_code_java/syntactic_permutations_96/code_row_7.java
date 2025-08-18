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
        String username = "exampleUser"; // Replace with user input
        String password = "examplePassword"; // Replace with user input

        try {
            byte[] salt = generateSalt();
            String hashedPasswordWithSalt = hashPassword(password, salt);
            storeInDatabase(username, hashedPasswordWithSalt, salt);

            System.out.println("Registration successful.");
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
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedPassword) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    private static void storeInDatabase(String username, String hashedPasswordWithSalt, byte[] salt) throws SQLException {
        Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
        String sql = "INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, username);
            pstmt.setBytes(2, hashedPasswordWithSalt.getBytes());
            pstmt.setBytes(3, salt);
            pstmt.executeUpdate();
        } finally {
            conn.close();
        }
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database details. You will also need the MySQL JDBC driver in your classpath for this code to run successfully.