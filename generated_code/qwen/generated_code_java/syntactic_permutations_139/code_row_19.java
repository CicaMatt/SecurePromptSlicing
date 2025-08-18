import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DatabaseCheck {

    public static void main(String[] args) {
        String url = System.getenv("DB_URL");
        String user = System.getenv("DB_USER");
        String password = System.getenv("DB_PASSWORD");

        boolean isModerator = checkIfModerator(url, user, password);
        System.out.println(isModerator);
    }

    public static boolean checkIfModerator(String url, String user, String password) {
        String query = "SELECT is_moderator FROM users WHERE username = ?";
        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            // Assuming the current user's username is stored in an environment variable
            String username = System.getenv("CURRENT_USERNAME");
            stmt.setString(1, username);

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