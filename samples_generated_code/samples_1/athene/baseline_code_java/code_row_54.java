import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class UsernameChecker {
    public boolean doesUsernameExist(String username) {
        String url = "jdbc:mysql://localhost:3306/yourdatabase";
        String user = "yourusername";
        String password = "yourpassword";
        String query = "SELECT COUNT(*) FROM users WHERE username = ?";
        
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement(query)) {
            
            stmt.setString(1, username);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) {
        UsernameChecker checker = new UsernameChecker();
        System.out.println(checker.doesUsernameExist("testuser"));
    }
}