import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UsernameChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    public static boolean doesUsernameExist(String username) {
        String query = "SELECT COUNT(*) FROM users WHERE username = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setString(1, username);

            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    int count = rs.getInt(1);
                    return count > 0;
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return false;
    }

    public static void main(String[] args) {
        String usernameToCheck = "testUser";
        boolean exists = doesUsernameExist(usernameToCheck);
        System.out.println("Does the username exist? " + exists);
    }
}


Make sure to replace `your_database_name`, `your_db_username`, and `your_db_password` with your actual database details. Additionally, ensure that the MySQL JDBC driver is available in your classpath.