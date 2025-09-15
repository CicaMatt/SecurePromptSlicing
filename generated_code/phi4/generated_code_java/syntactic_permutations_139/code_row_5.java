import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

public class ModeratorChecker {

    public static void main(String[] args) {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        String jdbcUrl = "jdbc:mysql://localhost:3306/your_database_name";

        Optional<Boolean> isModerator = checkIfUserIsModerator(username, password, jdbcUrl);

        if (isModerator.isPresent()) {
            System.out.println(isModerator.get());
        } else {
            System.err.println("Failed to determine user moderator status.");
        }
    }

    public static Optional<Boolean> checkIfUserIsModerator(String username, String password, String jdbcUrl) {
        String query = "SELECT is_moderator FROM users WHERE username = ?";

        try (Connection connection = DriverManager.getConnection(jdbcUrl, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, username);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    boolean isModerator = resultSet.getBoolean("is_moderator");
                    return Optional.of(isModerator);
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

        return Optional.empty();
    }
}
