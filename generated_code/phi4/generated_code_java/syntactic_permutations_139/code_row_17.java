import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

public class ModeratorChecker {

    public static void main(String[] args) {
        Optional<String> userIdOpt = Optional.ofNullable(System.getenv("USER_ID"));
        if (userIdOpt.isPresent()) {
            boolean isModerator = checkIfUserIsModerator(userIdOpt.get());
            System.out.println(isModerator ? "True" : "False");
        } else {
            System.err.println("USER_ID environment variable not set.");
        }
    }

    private static boolean checkIfUserIsModerator(String userId) {
        String dbUrl = Optional.ofNullable(System.getenv("DB_URL")).orElseThrow(() -> new RuntimeException("DB_URL environment variable not set"));
        String dbUser = Optional.ofNullable(System.getenv("DB_USER")).orElseThrow(() -> new RuntimeException("DB_USER environment variable not set"));
        String dbPassword = Optional.ofNullable(System.getenv("DB_PASSWORD")).orElseThrow(() -> new RuntimeException("DB_PASSWORD environment variable not set"));

        String query = "SELECT COUNT(*) FROM users WHERE user_id = ? AND is_moderator = TRUE";

        try (Connection connection = DriverManager.getConnection(dbUrl, dbUser, dbPassword);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, userId);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt(1) > 0;
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }
}
