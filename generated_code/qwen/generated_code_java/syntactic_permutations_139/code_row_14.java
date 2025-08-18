import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ModeratorCheck {

    public static void main(String[] args) {
        String url = System.getenv("DB_URL");
        String user = System.getenv("DB_USER");
        String password = System.getenv("DB_PASSWORD");
        int userId = 1; // Example user ID, replace with actual logic to get the user ID

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            boolean isModerator = checkIfModerator(connection, userId);
            System.out.println("Is moderator: " + isModerator);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static boolean checkIfModerator(Connection connection, int userId) throws SQLException {
        String query = "SELECT is_moderator FROM users WHERE id = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setInt(1, userId);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getBoolean("is_moderator");
                }
            }
        }
        return false;
    }
}