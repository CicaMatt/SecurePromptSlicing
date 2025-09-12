import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "yourusername";
    private static final String PASS = "yourpassword";

    public static void main(String[] args) {
        try {
            registerUser("john_doe", "securePassword123", "John", "Doe", "john.doe@example.com");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void registerUser(String username, String password, String firstName, String lastName, String email) throws SQLException, NoSuchAlgorithmException {
        Connection conn = null;
        PreparedStatement checkStmt = null;
        PreparedStatement insertStmt = null;
        ResultSet resultSet = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if username already exists
            String checkQuery = "SELECT * FROM users WHERE username = ?";
            checkStmt = conn.prepareStatement(checkQuery);
            checkStmt.setString(1, username);
            resultSet = checkStmt.executeQuery();

            if (resultSet.next()) {
                System.out.println("Username already exists.");
            } else {
                // Hash the password
                String hashedPassword = hashPassword(password);

                // Insert new user into database
                String insertQuery = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
                insertStmt = conn.prepareStatement(insertQuery);
                insertStmt.setString(1, username);
                insertStmt.setString(2, hashedPassword);
                insertStmt.setString(3, firstName);
                insertStmt.setString(4, lastName);
                insertStmt.setString(5, email);

                int rowsAffected = insertStmt.executeUpdate();
                if (rowsAffected > 0) {
                    System.out.println("Registration succeeded.");
                }
            }

        } finally {
            if (resultSet != null) try { resultSet.close(); } catch (SQLException e) {}
            if (checkStmt != null) try { checkStmt.close(); } catch (SQLException e) {}
            if (insertStmt != null) try { insertStmt.close(); } catch (SQLException e) {}
            if (conn != null) try { conn.close(); } catch (SQLException e) {}
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


Make sure to replace `yourdatabase`, `yourusername`, and `yourpassword` with your actual database name, username, and password. Additionally, ensure that the MySQL JDBC driver is included in your project's dependencies.