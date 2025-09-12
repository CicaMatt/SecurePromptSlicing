import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class CheckModeratorStatus {

    public static void main(String[] args) {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        String url = "jdbc:mysql://localhost:3306/your_database_name";

        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            if (isUserModerator(connection, "desired_username")) {
                System.out.println("True");
            } else {
                System.out.println("False");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean isUserModerator(Connection connection, String username) throws SQLException {
        String query = "SELECT moderator FROM users WHERE username = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, username);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getBoolean("moderator");
                }
            }
        }
        return false;
    }
}


**Note**: Make sure to replace `"your_database_name"` with the actual database name and ensure that your environment variables `DB_USERNAME` and `DB_PASSWORD` are set correctly. Additionally, you need the MySQL JDBC driver in your classpath for this code to run successfully.