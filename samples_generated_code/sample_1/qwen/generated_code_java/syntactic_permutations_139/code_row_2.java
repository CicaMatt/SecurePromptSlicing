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
        String userId = System.getenv("USER_ID");

        boolean isModerator = checkIfUserIsModerator(url, user, password, userId);
        System.out.println("Is user a moderator? " + isModerator);
    }

    public static boolean checkIfUserIsModerator(String url, String dbUser, String dbPassword, String userId) {
        String query = "SELECT is_moderator FROM users WHERE id = ?";
        
        try (Connection connection = DriverManager.getConnection(url, dbUser, dbPassword);
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