import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class UserRegistration {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        String username = "userExample";
        String password = "password123";

        try {
            // Hash the password
            String hashedPassword = hashPassword(password);

            // Insert into database
            insertUser(username, hashedPassword);
            
            System.out.println("User registered successfully.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hash = md.digest(password.getBytes());
        
        StringBuilder hexString = new StringBuilder(2 * hash.length);
        for (byte b : hash) {
            String hex = Integer.toHexString(0xff & b);
            if(hex.length() == 1) hexString.append('0');
            hexString.append(hex);
        }
        return hexString.toString();
    }

    private static void insertUser(String username, String hashedPassword) throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            // Connect to database
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // SQL query
            String sql = "INSERT INTO users (username, password_hash) VALUES (?, ?)";
            pstmt = conn.prepareStatement(sql);
            
            pstmt.setString(1, username);
            pstmt.setString(2, hashedPassword);

            // Execute the insert operation
            pstmt.executeUpdate();
        } finally {
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
    }
}
