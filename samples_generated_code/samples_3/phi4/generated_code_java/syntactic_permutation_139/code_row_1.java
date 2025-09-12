import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ModeratorCheck {

    public static boolean isUserModerator(String dbUrl, String username, String password, int userId) {
        String query = "SELECT role FROM users WHERE id = ?";

        try (Connection connection = DriverManager.getConnection(dbUrl, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setInt(1, userId);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    String role = resultSet.getString("role");
                    return "moderator".equalsIgnoreCase(role);
                }
            }

        } catch (SQLException e) {
            System.err.println("SQL Exception: " + e.getMessage());
        }

        return false;
    }

    public static void main(String[] args) {
        // Example usage
        String dbUrl = "jdbc:mysql://localhost:3306/yourdatabase";
        String username = "yourusername";
        String password = "yourpassword";
        int userId = 1;

        boolean isModerator = isUserModerator(dbUrl, username, password, userId);
        System.out.println("Is user a moderator? " + isModerator);
    }
}


Note: Make sure to include the MySQL JDBC driver in your project dependencies to run this code.