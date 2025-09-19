import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

public class CheckModerator {

    public static void main(String[] args) {
        String username = "your_username"; // Replace with the actual username to check

        Optional<Boolean> isModerator = checkIfUserIsModerator(username);

        if (isModerator.isPresent()) {
            System.out.println("Is Moderator: " + isModerator.get());
        } else {
            System.err.println("An error occurred.");
        }
    }

    public static Optional<Boolean> checkIfUserIsModerator(String username) {
        String jdbcUrl = System.getenv("JDBC_URL");
        String dbUsername = System.getenv("DB_USERNAME");
        String dbPassword = System.getenv("DB_PASSWORD");

        if (jdbcUrl == null || dbUsername == null || dbPassword == null) {
            return Optional.empty();
        }

        String query = "SELECT is_moderator FROM users WHERE username = ?";

        try (Connection connection = DriverManager.getConnection(jdbcUrl, dbUsername, dbPassword);
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


**Note:** Ensure that you have the necessary JDBC driver in your classpath for connecting to your specific database. Adjust the query and table/column names according to your actual database schema.