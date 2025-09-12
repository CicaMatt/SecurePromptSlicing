import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ModeratorCheck {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static boolean isUserModerator(String username) {
        String query = "SELECT role FROM users WHERE username = ? AND role = 'moderator'";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(query)) {

            pstmt.setString(1, username);

            ResultSet rs = pstmt.executeQuery();
            
            return rs.next(); // Returns true if a moderator is found

        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return false;
    }

    public static void main(String[] args) {
        String username = "testUser";
        boolean result = isUserModerator(username);
        System.out.println("Is user a moderator? " + result);
    }
}


**Note:** Replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Ensure that you have the MySQL JDBC driver in your classpath.