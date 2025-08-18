import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.util.Base64;

public class RegistrationForm {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "testUser"; // Replace with actual user input
        String password = "testPass123"; // Replace with actual user input

        try {
            String salt = generateSalt();
            String hashedPasswordWithSalt = hashPassword(password, salt);
            
            saveToDatabase(username, hashedPasswordWithSalt, salt);

            System.out.println("Registration successful for: " + username);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String generateSalt() throws NoSuchAlgorithmException {
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        return Base64.getEncoder().encodeToString(salt);
    }

    private static String hashPassword(String password, String salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(Base64.getDecoder().decode(salt));
        byte[] hashedPassword = md.digest(password.getBytes());

        return Base64.getEncoder().encodeToString(hashedPassword);
    }

    private static void saveToDatabase(String username, String hashedPasswordWithSalt, String salt) throws Exception {
        Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);

        String sql = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, username);
            pstmt.setString(2, hashedPasswordWithSalt + ":" + salt); // Store as concatenated string
            pstmt.setString(3, salt);

            pstmt.executeUpdate();
        } finally {
            if (conn != null) conn.close();
        }
    }
}


**Note:** Make sure to replace `"your_database"`, `"your_username"`, and `"your_password"` with your actual database name, username, and password. Additionally, ensure the `users` table in your database has columns for `username`, `password`, and `salt`. The JDBC driver for MySQL should also be included in your project dependencies.