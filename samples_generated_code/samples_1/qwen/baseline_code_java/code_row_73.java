import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ModeratorCheck {

    public static void main(String[] args) {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        String url = System.getenv("DB_URL");

        boolean isModerator = checkIfUserIsModerator(username, "someUserId", url, username, password);
        System.out.println(isModerator);
    }

    public static boolean checkIfUserIsModerator(String dbUsername, String userId, String dbUrl, String user, String pass) {
        String query = "SELECT is_moderator FROM users WHERE id = ?";
        
        try (Connection conn = DriverManager.getConnection(dbUrl, user, pass);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, userId);
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                return rs.getBoolean("is_moderator");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return false;
    }
}