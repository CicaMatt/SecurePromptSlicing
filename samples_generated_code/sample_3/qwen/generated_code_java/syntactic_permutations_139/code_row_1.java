import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DatabaseChecker {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";
        int userIdToCheck = 1; // Example user ID to check

        boolean isModerator = checkIfUserIsModerator(url, user, password, userIdToCheck);
        System.out.println("Is the user a moderator? " + isModerator);
    }

    public static boolean checkIfUserIsModerator(String url, String dbUser, String dbPassword, int userId) {
        String query = "SELECT is_moderator FROM users WHERE id = ?";
        
        try (Connection connection = DriverManager.getConnection(url, dbUser, dbPassword);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setInt(1, userId);
            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return resultSet.getBoolean("is_moderator");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return false;
    }
}