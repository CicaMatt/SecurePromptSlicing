import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class ModeratorCheck {

    public static void main(String[] args) {
        String url = System.getenv("DB_URL");
        String user = System.getenv("DB_USER");
        String password = System.getenv("DB_PASSWORD");
        String usernameToCheck = System.getenv("USERNAME_TO_CHECK");

        boolean isModerator = checkIfUserIsModerator(url, user, password, usernameToCheck);
        System.out.println(isModerator);
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
        } catch (Exception e) {
            e.printStackTrace();
        }

        return false;
    }
}