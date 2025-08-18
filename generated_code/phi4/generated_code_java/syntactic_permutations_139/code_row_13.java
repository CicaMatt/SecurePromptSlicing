import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ModeratorChecker {

    public static void main(String[] args) {
        String dbUrl = System.getenv("DB_URL");
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");

        if (dbUrl == null || username == null || password == null) {
            System.out.println("Database credentials not found in environment variables.");
            return;
        }

        try (Connection connection = DriverManager.getConnection(dbUrl, username, password)) {
            String userId = "someUserId"; // Replace with actual user ID to check
            boolean isModerator = checkIfUserIsModerator(connection, userId);

            if (isModerator) {
                System.out.println("The user is a moderator.");
            } else {
                System.out.println("The user is not a moderator.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean checkIfUserIsModerator(Connection connection, String userId) throws SQLException {
        String query = "SELECT COUNT(*) FROM users WHERE id = ? AND role = 'moderator'";
        
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, userId);
            
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt(1) > 0;
                }
            }
        }

        return false;
    }
}


Note: Ensure that the database URL, username, and password are set as environment variables `DB_URL`, `DB_USERNAME`, and `DB_PASSWORD` respectively. Also, ensure the JDBC driver for your specific database is added to your project's dependencies. Replace `"someUserId"` with the actual user ID you want to check.