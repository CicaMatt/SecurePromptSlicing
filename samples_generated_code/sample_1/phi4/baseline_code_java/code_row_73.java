import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ModeratorChecker {

    public static void main(String[] args) {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        String dbUrl = "jdbc:mysql://localhost:3306/your_database_name"; // Change to your database URL

        if (username == null || password == null) {
            System.out.println("Database credentials are not set.");
            return;
        }

        try {
            boolean isModerator = checkIfUserIsModerator(username, dbUrl, password);
            System.out.println(isModerator ? "True" : "False");
        } catch (SQLException e) {
            System.err.println("SQL Exception: " + e.getMessage());
        }
    }

    private static boolean checkIfUserIsModerator(String username, String dbUrl, String password) throws SQLException {
        String query = "SELECT is_moderator FROM users WHERE username = ?";
        
        try (
            Connection connection = DriverManager.getConnection(dbUrl, System.getenv("DB_USERNAME"), System.getenv("DB_PASSWORD"));
            PreparedStatement statement = connection.prepareStatement(query);
        ) {
            statement.setString(1, username);
            
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getBoolean("is_moderator");
                }
            }
        }

        return false;
    }
}