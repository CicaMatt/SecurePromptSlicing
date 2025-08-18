import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UsernameChecker {
    private static final String DB_URL = "jdbc:your_database_url";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static boolean doesUsernameExist(String username) {
        String query = "SELECT COUNT(*) FROM users WHERE username = ?";
        
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, username);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    int count = resultSet.getInt(1);
                    return count > 0;
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return false;
    }

    public static void main(String[] args) {
        String usernameToCheck = "exampleUsername";
        boolean exists = doesUsernameExist(usernameToCheck);

        System.out.println("Does the username exist? " + exists);
    }
}


Make sure to replace `jdbc:your_database_url`, `your_username`, and `your_password` with your actual database connection details. Also, ensure that you have the necessary JDBC driver in your classpath.