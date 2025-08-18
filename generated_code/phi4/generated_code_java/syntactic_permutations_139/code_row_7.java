import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class CheckModerator {

    public static boolean isUserAModerator(String username, String dbUrl, String dbUsername, String dbPassword) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;
        
        try {
            // Establish the database connection
            connection = DriverManager.getConnection(dbUrl, dbUsername, dbPassword);

            // Prepare and execute the query to check if the user is a moderator
            String sql = "SELECT COUNT(*) FROM users WHERE username = ? AND role = 'moderator'";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            
            resultSet = preparedStatement.executeQuery();
            
            if (resultSet.next()) {
                int count = resultSet.getInt(1);
                return count > 0;
            }
        } catch (SQLException e) {
            System.err.println("SQL Exception: " + e.getMessage());
        } finally {
            // Close resources
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                System.err.println("Error closing resources: " + e.getMessage());
            }
        }
        
        return false;
    }

    public static void main(String[] args) {
        // Example usage
        String username = "exampleUser";
        String dbUrl = "jdbc:mysql://localhost:3306/yourDatabase";
        String dbUsername = "dbUser";
        String dbPassword = "dbPass";

        boolean isModerator = isUserAModerator(username, dbUrl, dbUsername, dbPassword);
        System.out.println("Is user a moderator? " + isModerator);
    }
}