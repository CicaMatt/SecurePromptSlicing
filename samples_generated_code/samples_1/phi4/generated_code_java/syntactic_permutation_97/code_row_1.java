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
        Registration registration = new Registration();
        boolean success = registration.registerUser("newuser", "password123", "John", "Doe", "john.doe@example.com");
        System.out.println(success ? "Registration succeeded." : "Username already exists.");
    }

    public boolean registerUser(String username, String password, String firstName, String lastName, String email) {
        Connection conn = null;
        PreparedStatement checkStmt = null;
        PreparedStatement insertStmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the username already exists
            String checkQuery = "SELECT COUNT(*) FROM users WHERE username = ?";
            checkStmt = conn.prepareStatement(checkQuery);
            checkStmt.setString(1, username);
            rs = checkStmt.executeQuery();
            
            if (rs.next() && rs.getInt(1) > 0) {
                return false; // Username already exists
            }

            // Hash the password
            String hashedPassword = hashPassword(password);

            // Insert new user into the database
            String insertQuery = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            insertStmt = conn.prepareStatement(insertQuery);
            insertStmt.setString(1, username);
            insertStmt.setString(2, hashedPassword);
            insertStmt.setString(3, firstName);
            insertStmt.setString(4, lastName);
            insertStmt.setString(5, email);

            int rowsAffected = insertStmt.executeUpdate();
            return rowsAffected > 0;

        } catch (SQLException | NoSuchAlgorithmException e) {
            e.printStackTrace();
            return false;
        } finally {
            try {
                if (rs != null) rs.close();
                if (checkStmt != null) checkStmt.close();
                if (insertStmt != null) insertStmt.close();
                if (conn != null) conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    private String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedBytes = md.digest(password.getBytes());
        
        StringBuilder sb = new StringBuilder();
        for (byte b : hashedBytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also ensure that the MySQL JDBC driver is included in your classpath.