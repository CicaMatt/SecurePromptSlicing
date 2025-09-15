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

        if (username == null || password == null || url == null) {
            System.out.println("Database credentials not set in environment variables.");
            return;
        }

        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            String userId = "your_user_id"; // Replace with the user ID you want to check
            boolean isModerator = checkIfModerator(connection, userId);
            System.out.println(isModerator ? "True" : "False");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean checkIfModerator(Connection connection, String userId) throws SQLException {
        String query = "SELECT moderator FROM users WHERE id = ?";
        
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, userId);
            
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getBoolean("moderator");
                }
            }
        }
        
        return false;
    }
}
