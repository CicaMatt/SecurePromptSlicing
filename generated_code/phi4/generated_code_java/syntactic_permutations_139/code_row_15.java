import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ModeratorCheck {

    public static void main(String[] args) {
        String dbUrl = System.getenv("DB_URL");
        String dbUser = System.getenv("DB_USER");
        String dbPassword = System.getenv("DB_PASSWORD");

        if (dbUrl == null || dbUser == null || dbPassword == null) {
            System.out.println("Database credentials are not set in environment variables.");
            return;
        }

        try (Connection connection = DriverManager.getConnection(dbUrl, dbUser, dbPassword)) {
            String query = "SELECT is_moderator FROM users WHERE username = ?";
            PreparedStatement preparedStatement = connection.prepareStatement(query);

            // Replace 'username' with the actual username you want to check
            preparedStatement.setString(1, "username");

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    boolean isModerator = resultSet.getBoolean("is_moderator");
                    System.out.println("Is Moderator: " + isModerator);
                } else {
                    System.out.println("User not found.");
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
