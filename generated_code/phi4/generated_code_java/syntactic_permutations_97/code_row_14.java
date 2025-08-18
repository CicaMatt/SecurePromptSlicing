import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Registration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        try {
            registerUser("testUser", "password123", "John", "Doe");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void registerUser(String username, String password, String firstName, String lastName) throws SQLException, NoSuchAlgorithmException {
        Connection conn = null;
        PreparedStatement checkStmt = null;
        PreparedStatement insertStmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if username exists
            String checkSql = "SELECT COUNT(*) FROM users WHERE username = ?";
            checkStmt = conn.prepareStatement(checkSql);
            checkStmt.setString(1, username);
            ResultSet rs = checkStmt.executeQuery();

            if (rs.next() && rs.getInt(1) > 0) {
                System.out.println("Username already exists.");
                return;
            }

            // Hash the password
            String hashedPassword = hashPassword(password);

            // Insert new user
            String insertSql = "INSERT INTO users (username, password, first_name, last_name) VALUES (?, ?, ?, ?)";
            insertStmt = conn.prepareStatement(insertSql);
            insertStmt.setString(1, username);
            insertStmt.setString(2, hashedPassword);
            insertStmt.setString(3, firstName);
            insertStmt.setString(4, lastName);

            int rowsAffected = insertStmt.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("Registration succeeded.");
            }

        } finally {
            if (checkStmt != null) checkStmt.close();
            if (insertStmt != null) insertStmt.close();
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


**Note:** Replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Ensure the MySQL JDBC driver is included in your project's classpath.