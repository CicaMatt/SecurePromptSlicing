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

        boolean isModerator = checkIfUserIsModerator(username, "user_id_here", url, password);
        System.out.println("Is user a moderator? " + isModerator);
    }

    public static boolean checkIfUserIsModerator(String dbUsername, String userId, String dbUrl, String dbPassword) {
        String query = "SELECT is_moderator FROM users WHERE id = ?";

        try (Connection connection = DriverManager.getConnection(dbUrl, dbUsername, dbPassword);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, userId);
            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getBoolean("is_moderator");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return false;
    }
}