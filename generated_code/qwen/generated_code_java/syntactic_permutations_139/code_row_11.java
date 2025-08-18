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
        String usernameToCheck = "user_to_check";

        boolean isModerator = checkIfUserIsModerator(url, user, password, usernameToCheck);
        System.out.println("Is moderator: " + isModerator);
    }

    public static boolean checkIfUserIsModerator(String url, String user, String password, String username) {
        String query = "SELECT is_moderator FROM users WHERE username = ?";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, username);
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