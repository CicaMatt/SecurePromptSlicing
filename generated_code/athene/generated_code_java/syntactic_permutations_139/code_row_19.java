import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Objects;

public class ModeratorChecker {

    public static boolean isModerator(String username) {
        String dbURL = Objects.requireNonNullElse(System.getenv("DB_URL"), "");
        String dbUser = Objects.requireNonNullElse(System.getenv("DB_USER"), "");
        String dbPassword = Objects.requireNonNullElse(System.getenv("DB_PASSWORD"), "");

        try (Connection connection = DriverManager.getConnection(dbURL, dbUser, dbPassword)) {
            String query = "SELECT is_moderator FROM users WHERE username = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, username);
                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        return resultSet.getBoolean("is_moderator");
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) {
        System.out.println(isModerator(args[0]));
    }
}