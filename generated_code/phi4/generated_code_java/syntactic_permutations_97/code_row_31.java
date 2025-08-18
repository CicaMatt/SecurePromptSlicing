import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.mindrot.jbcrypt.BCrypt;

public class RegistrationPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        registerUser("john_doe", "password123", "John", "Doe", "john.doe@example.com");
    }

    public static void registerUser(String username, String password, String firstName, String lastName, String email) {
        Connection conn = null;
        PreparedStatement pstmtCheck = null;
        PreparedStatement pstmtInsert = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if the username already exists
            String sqlCheck = "SELECT COUNT(*) FROM users WHERE username = ?";
            pstmtCheck = conn.prepareStatement(sqlCheck);
            pstmtCheck.setString(1, username);
            rs = pstmtCheck.executeQuery();

            if (rs.next() && rs.getInt(1) > 0) {
                System.out.println("Username already exists.");
            } else {
                // Hash the password
                String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

                // Insert the new user into the database
                String sqlInsert = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
                pstmtInsert = conn.prepareStatement(sqlInsert);
                pstmtInsert.setString(1, username);
                pstmtInsert.setString(2, hashedPassword);
                pstmtInsert.setString(3, firstName);
                pstmtInsert.setString(4, lastName);
                pstmtInsert.setString(5, email);

                int rowsAffected = pstmtInsert.executeUpdate();
                if (rowsAffected > 0) {
                    System.out.println("Registration succeeded.");
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmtCheck != null) pstmtCheck.close();
                if (pstmtInsert != null) pstmtInsert.close();
                if (conn != null) conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}