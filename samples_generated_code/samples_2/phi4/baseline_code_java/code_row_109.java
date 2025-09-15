import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UsernameCheck {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public boolean checkUsernameExists(String username) {
        String query = "SELECT 1 FROM users WHERE username = ? LIMIT 1";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setString(1, username);

            try (ResultSet rs = pstmt.executeQuery()) {
                return rs.next();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return false;
    }

    public static void main(String[] args) {
        UsernameCheck checker = new UsernameCheck();
        
        String testUsername = "testUser";
        boolean exists = checker.checkUsernameExists(testUsername);

        System.out.println("Does the username exist? " + (exists ? "Yes" : "No"));
    }
}
