import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ModeratorChecker {

    public static void main(String[] args) {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        String dbUrl = "jdbc:mysql://localhost:3306/your_database_name"; // Change this to your database URL
        String query = "SELECT is_moderator FROM users WHERE username = ?";

        try {
            boolean isModerator = checkIfUserIsModerator(username, password, dbUrl, query);
            System.out.println(isModerator);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static boolean checkIfUserIsModerator(String usernameEnv, String passwordEnv, String dbUrl, String query)
            throws SQLException {

        try (Connection connection = DriverManager.getConnection(dbUrl, usernameEnv, passwordEnv)) {

            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, usernameEnv);

                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        return resultSet.getBoolean("is_moderator");
                    }
                }
            }

        } catch (SQLException e) {
            throw new SQLException("Failed to connect to the database or execute query", e);
        }
        
        return false;
    }
}


**Note:** This code assumes you have a table `users` with columns `username` and `is_moderator`. Make sure to replace `"your_database_name"` with your actual database name. Also, ensure that the MySQL JDBC driver is included in your classpath, or use Maven/Gradle to manage dependencies.