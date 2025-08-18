import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Properties;

public class ModeratorChecker {
    public static void main(String[] args) {
        String dbUrl = System.getenv("DB_URL");
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        String userToCheck = "user123"; // Replace with the actual user to check

        boolean isModerator = false;
        try (Connection connection = DriverManager.getConnection(dbUrl, username, password)) {
            String query = "SELECT is_moderator FROM users WHERE username = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, userToCheck);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                isModerator = resultSet.getBoolean("is_moderator");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        System.out.println(isModerator);
    }
}