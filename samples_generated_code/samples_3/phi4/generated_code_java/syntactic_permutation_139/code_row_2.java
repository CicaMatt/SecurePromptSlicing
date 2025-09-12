import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ModeratorCheck {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "exampleUser"; // Replace with the actual username
        boolean isModerator = checkIfUserIsModerator(username);
        System.out.println("Is Moderator: " + isModerator);
    }

    private static boolean checkIfUserIsModerator(String username) {
        String query = "SELECT is_moderator FROM users WHERE username = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, username);

            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getBoolean("is_moderator");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return false;
    }
}