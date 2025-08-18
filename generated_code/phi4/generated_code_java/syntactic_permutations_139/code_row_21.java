import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ModeratorChecker {

    public static void main(String[] args) {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        String url = System.getenv("DB_URL");

        if (username == null || password == null || url == null) {
            System.out.println("Database credentials are not set in environment variables.");
            return;
        }

        try {
            Connection connection = DriverManager.getConnection(url, username, password);
            boolean isModerator = checkIfUserIsModerator(connection, "yourUserId");
            System.out.println(isModerator ? "True" : "False");

            connection.close();
        } catch (SQLException e) {
            System.out.println("Database connection error: " + e.getMessage());
        }
    }

    private static boolean checkIfUserIsModerator(Connection connection, String userId) throws SQLException {
        String query = "SELECT is_moderator FROM users WHERE user_id = ?";
        
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, userId);
            
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getBoolean("is_moderator");
                }
            }
        }

        return false;
    }
}


Make sure to replace `"yourUserId"` with the appropriate user ID you want to check. Also, ensure that your database driver is available in the classpath when running this code.