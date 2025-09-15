import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "testUser"; // Example username
        String password = "testPassword"; // Example password

        try {
            registerUser(username, password);
            System.out.println("Registration successful");
        } catch (Exception e) {
            System.err.println("Error during registration: " + e.getMessage());
        }
    }

    private static void registerUser(String username, String password) throws SQLException, NoSuchAlgorithmException {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            // Establish database connection
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Hash the password
            String hashedPassword = hashPassword(password);

            // Prepare SQL statement
            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, hashedPassword);

            // Execute the insertion
            pstmt.executeUpdate();
        } finally {
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());
        
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}
