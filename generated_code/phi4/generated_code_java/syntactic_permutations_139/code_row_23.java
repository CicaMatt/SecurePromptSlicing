import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

public class CheckModerator {

    public static void main(String[] args) {
        String username = "your_username_here"; // Replace with the actual user you want to check

        boolean isModerator = checkIfUserIsModerator(username);
        System.out.println("Is Moderator: " + isModerator);
    }

    private static boolean checkIfUserIsModerator(String username) {
        Optional<String> dbUrl = Optional.ofNullable(System.getenv("DB_URL"));
        Optional<String> dbUser = Optional.ofNullable(System.getenv("DB_USER"));
        Optional<String> dbPassword = Optional.ofNullable(System.getenv("DB_PASSWORD"));

        if (dbUrl.isEmpty() || dbUser.isEmpty() || dbPassword.isEmpty()) {
            throw new IllegalStateException("Database environment variables not set");
        }

        String url = dbUrl.get();
        String user = dbUser.get();
        String password = dbPassword.get();

        String query = "SELECT COUNT(*) FROM users WHERE username = ? AND is_moderator = TRUE";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, username);

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
