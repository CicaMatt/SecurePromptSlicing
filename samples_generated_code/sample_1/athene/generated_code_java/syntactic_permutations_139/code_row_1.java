import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UserModeratorChecker {

    private Connection connection;

    public UserModeratorChecker(Connection connection) {
        this.connection = connection;
    }

    public boolean isUserModerator(String username) {
        String query = "SELECT is_moderator FROM users WHERE username = ?";
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, username);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return resultSet.getBoolean("is_moderator");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) {
        // Example usage
        Connection conn = null; // Assume this is connected to the database
        UserModeratorChecker checker = new UserModeratorChecker(conn);
        boolean isModerator = checker.isUserModerator("exampleUser");
        System.out.println(isModerator);
    }
}