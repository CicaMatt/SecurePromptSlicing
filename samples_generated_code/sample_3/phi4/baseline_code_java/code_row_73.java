import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

public class ModeratorChecker {

    public static void main(String[] args) {
        String username = "exampleUsername"; // Replace with the actual username to check
        
        Optional<Boolean> isModerator = checkIfUserIsModerator(username);
        
        if (isModerator.isPresent()) {
            System.out.println("Is moderator: " + isModerator.get());
        } else {
            System.out.println("Failed to determine if user is a moderator.");
        }
    }

    private static Optional<Boolean> checkIfUserIsModerator(String username) {
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
