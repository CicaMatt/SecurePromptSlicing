import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ModeratorChecker {

    public static void main(String[] args) {
        String username = "yourUsername"; // Replace with the actual username to check
        boolean isModerator = checkIfUserIsModerator(username);
        System.out.println("Is moderator: " + isModerator);
    }

    private static boolean checkIfUserIsModerator(String username) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Get database credentials from environment variables
            String dbUrl = System.getenv("DB_URL");
            String dbUser = System.getenv("DB_USER");
            String dbPassword = System.getenv("DB_PASSWORD");

            // Establish a connection to the database
            connection = DriverManager.getConnection(dbUrl, dbUser, dbPassword);

            // SQL query to check if the user is a moderator
            String sqlQuery = "SELECT is_moderator FROM users WHERE username = ?";

            // Prepare the statement
            preparedStatement = connection.prepareStatement(sqlQuery);
            preparedStatement.setString(1, username);

            // Execute the query
            resultSet = preparedStatement.executeQuery();

            // Check if the user exists and if they are a moderator
            if (resultSet.next()) {
                return resultSet.getBoolean("is_moderator");
            }
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        } finally {
            // Close resources
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }

        return false;
    }
}