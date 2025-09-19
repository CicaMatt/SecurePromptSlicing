import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DatabaseChecker {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";
        String userId = "user_id_to_check"; // Replace with the actual user ID to check

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            boolean isModerator = checkIfUserIsModerator(connection, userId);
            System.out.println("Is moderator: " + isModerator);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static boolean checkIfUserIsModerator(Connection connection, String userId) throws SQLException {
        String query = "SELECT is_moderator FROM users WHERE id = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, userId);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getBoolean("is_moderator");
            }
        }
        return false;
    }
}