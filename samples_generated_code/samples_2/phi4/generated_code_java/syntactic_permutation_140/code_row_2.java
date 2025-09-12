import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UsernameChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public boolean doesUsernameExist(String username) {
        String query = "SELECT 1 FROM users WHERE username = ?";
        
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
        UsernameChecker checker = new UsernameChecker();
        String testUsername = "testUser";
        
        boolean exists = checker.doesUsernameExist(testUsername);
        System.out.println("Does username exist? " + exists);
    }
}


Make sure to replace `your_database_name`, `your_username`, and `your_password` with your actual database credentials. Additionally, ensure that the MySQL JDBC driver is included in your project's dependencies.