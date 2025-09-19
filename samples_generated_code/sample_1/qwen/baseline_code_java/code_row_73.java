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
        String userToCheck = "exampleUser"; // Replace with the actual username to check

        boolean isModerator = checkIfModerator(url, username, password, userToCheck);
        System.out.println("Is moderator: " + isModerator);
    }

    public static boolean checkIfModerator(String url, String dbUsername, String dbPassword, String user) {
        String query = "SELECT is_moderator FROM users WHERE username = ?";

        try (Connection connection = DriverManager.getConnection(url, dbUsername, dbPassword);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, user);
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