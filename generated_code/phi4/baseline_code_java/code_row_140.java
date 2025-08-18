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
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, username);

            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return false;
    }

    public static void main(String[] args) {
        String usernameToCheck = "testuser";
        boolean exists = doesUsernameExist(usernameToCheck);
        System.out.println("Does username exist? " + exists);
    }
}


**Note:** Replace `your_database_name`, `your_db_username`, and `your_db_password` with your actual database name, username, and password. Ensure the MySQL JDBC driver is included in your project's classpath.