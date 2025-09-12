import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class CheckModerator {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String username = "your_username";
        String password = "your_password";

        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            boolean isModerator = checkIfUserIsModerator(connection, "username_to_check");
            System.out.println(isModerator);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static boolean checkIfUserIsModerator(Connection connection, String userToCheck) throws SQLException {
        String query = "SELECT 1 FROM users WHERE username = ? AND is_moderator = TRUE LIMIT 1";
        
        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, userToCheck);
            
            try (ResultSet resultSet = statement.executeQuery()) {
                return resultSet.next();
            }
        }
    }
}


**Note:** Replace `"jdbc:mysql://localhost:3306/your_database"`, `"your_username"`, and `"your_password"` with your actual database URL, username, and password. Also, adjust the table name `users` and column names `username` and `is_moderator` to match your database schema.