import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

public class ModeratorChecker {

    public static void main(String[] args) {
        String username = "exampleUser"; // Replace with the actual user to check

        Optional<Boolean> isModerator = isUserAModerator(username);
        isModerator.ifPresent(moderatorStatus -> System.out.println("Is moderator: " + moderatorStatus));
    }

    private static Optional<Boolean> isUserAModerator(String username) {
        String dbUrl = System.getenv("DB_URL");
        String dbUsername = System.getenv("DB_USERNAME");
        String dbPassword = System.getenv("DB_PASSWORD");

        if (dbUrl == null || dbUsername == null || dbPassword == null) {
            return Optional.empty();
        }

        String query = "SELECT is_moderator FROM users WHERE username = ?";

        try (Connection connection = DriverManager.getConnection(dbUrl, dbUsername, dbPassword);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, username);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return Optional.of(resultSet.getBoolean("is_moderator"));
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

        return Optional.empty();
    }
}
