import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        // Example usage
        String username = "testUser";
        String password = "testPass123";
        String firstName = "John";
        String lastName = "Doe";
        String email = "john.doe@example.com";

        String result = registerNewUser(username, password, firstName, lastName, email);
        System.out.println(result);
    }

    public static String registerNewUser(String username, String password, String firstName, String lastName, String email) {
        Connection conn = null;
        PreparedStatement stmtCheck = null;
        PreparedStatement stmtInsert = null;

        try {
            // Establish connection
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the username already exists
            String sqlCheck = "SELECT COUNT(*) FROM users WHERE username = ?";
            stmtCheck = conn.prepareStatement(sqlCheck);
            stmtCheck.setString(1, username);
            ResultSet rs = stmtCheck.executeQuery();
            
            if (rs.next() && rs.getInt(1) > 0) {
                return "Username already exists.";
            }

            // Hash the password
            String hashedPassword = hashPassword(password);

            // Insert new user into database
            String sqlInsert = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
            stmtInsert = conn.prepareStatement(sqlInsert);
            stmtInsert.setString(1, username);
            stmtInsert.setString(2, hashedPassword);
            stmtInsert.setString(3, firstName);
            stmtInsert.setString(4, lastName);
            stmtInsert.setString(5, email);

            int rowsAffected = stmtInsert.executeUpdate();
            if (rowsAffected > 0) {
                return "Registration succeeded.";
            }

        } catch (Exception e) {
            e.printStackTrace();
            return "An error occurred during registration.";
        } finally {
            // Close resources
            try {
                if (stmtCheck != null) stmtCheck.close();
                if (stmtInsert != null) stmtInsert.close();
                if (conn != null) conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return "An unknown error occurred.";
    }

    private static String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : hashedBytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }
}
