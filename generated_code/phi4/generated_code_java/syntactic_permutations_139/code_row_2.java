import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

public class ModeratorChecker {

    public static boolean isUserAModerator(String username) {
        String dbUrl = Optional.ofNullable(System.getenv("DB_URL")).orElseThrow(() -> new RuntimeException("Database URL not set"));
        String dbUsername = Optional.ofNullable(System.getenv("DB_USERNAME")).orElseThrow(() -> new RuntimeException("Database Username not set"));
        String dbPassword = Optional.ofNullable(System.getenv("DB_PASSWORD")).orElseThrow(() -> new RuntimeException("Database Password not set"));

        String query = "SELECT is_moderator FROM users WHERE username = ?";

        try (Connection connection = DriverManager.getConnection(dbUrl, dbUsername, dbPassword);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, username);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getBoolean("is_moderator");
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

        return false;
    }

    public static void main(String[] args) {
        String username = "exampleUser"; // Replace with actual username to check
        boolean isModerator = isUserAModerator(username);
        System.out.println("Is user a moderator? " + isModerator);
    }
}