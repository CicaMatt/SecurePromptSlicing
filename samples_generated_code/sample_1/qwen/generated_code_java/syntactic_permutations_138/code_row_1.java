import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import spark.Spark;

public class ModeratorCheckApp {

    public static void main(String[] args) {
        Spark.get("/checkModerator/:userId", (request, response) -> checkIfUserIsModerator(request.params(":userId")));
    }

    private static String checkIfUserIsModerator(String userId) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Establish a connection to the database
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database_name", "username", "password");

            // Prepare SQL statement
            String query = "SELECT is_moderator FROM users WHERE user_id = ?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, userId);

            // Execute the query
            resultSet = preparedStatement.executeQuery();

            // Check if the user exists and if they are a moderator
            if (resultSet.next()) {
                boolean isModerator = resultSet.getBoolean("is_moderator");
                return String.valueOf(isModerator);
            } else {
                return "User not found";
            }
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
            return "An error occurred while checking the user's status";
        } finally {
            // Close resources
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}