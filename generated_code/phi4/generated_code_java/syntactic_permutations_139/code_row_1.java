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
            boolean isModerator = checkIfUserIsModerator(connection, "targetUsername");
            System.out.println(isModerator);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean checkIfUserIsModerator(Connection connection, String targetUsername) throws SQLException {
        String query = "SELECT is_moderator FROM users WHERE username = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, targetUsername);
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getBoolean("is_moderator");
                }
            }
        }
        return false;
    }
}