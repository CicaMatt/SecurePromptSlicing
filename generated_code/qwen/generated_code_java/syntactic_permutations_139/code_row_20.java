import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DatabaseChecker {

    public static void main(String[] args) {
        String user = System.getenv("DB_USER");
        String password = System.getenv("DB_PASSWORD");
        String url = System.getenv("DB_URL");

        boolean isModerator = checkIfUserIsModerator(user, password, url, "usernameToCheck");
        System.out.println("Is the user a moderator? " + isModerator);
    }

    public static boolean checkIfUserIsModerator(String dbUser, String dbPassword, String dbUrl, String username) {
        String query = "SELECT is_moderator FROM users WHERE username = ?";
        
        try (Connection connection = DriverManager.getConnection(dbUrl, dbUser, dbPassword);
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