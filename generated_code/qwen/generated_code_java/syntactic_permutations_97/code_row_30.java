import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "testuser";
        String password = "password123";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        if (registerUser(username, password, firstName, lastName, email)) {
            System.out.println("Registration succeeded.");
        } else {
            System.out.println("Username already exists.");
        }
    }

    private static boolean registerUser(String username, String password, String firstName, String lastName, String email) {
        Connection conn = null;
        PreparedStatement pstmtSelect = null;
        PreparedStatement pstmtInsert = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the username already exists
            String sqlSelect = "SELECT * FROM users WHERE username = ?";
            pstmtSelect = conn.prepareStatement(sqlSelect);
            pstmtSelect.setString(1, username);
            rs = pstmtSelect.executeQuery();

            if (rs.next()) {
                return false; // Username already exists
            }

            // Hash the password
            String hashedPassword = hashPassword(password);

            // Insert new user into the database
            String sqlInsert = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            pstmtInsert = conn.prepareStatement(sqlInsert);
            pstmtInsert.setString(1, username);
            pstmtInsert.setString(2, hashedPassword);
            pstmtInsert.setString(3, firstName);
            pstmtInsert.setString(4, lastName);
            pstmtInsert.setString(5, email);

            int rowsAffected = pstmtInsert.executeUpdate();
            return rowsAffected > 0;

        } catch (SQLException | NoSuchAlgorithmException e) {
            e.printStackTrace();
            return false;
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmtSelect != null) pstmtSelect.close();
                if (pstmtInsert != null) pstmtInsert.close();
                if (conn != null) conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
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