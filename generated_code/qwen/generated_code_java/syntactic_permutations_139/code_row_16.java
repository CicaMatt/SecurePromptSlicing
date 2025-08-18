import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DatabaseChecker {

    public static void main(String[] args) {
        String url = System.getenv("DB_URL");
        String user = System.getenv("DB_USER");
        String password = System.getenv("DB_PASSWORD");
        String usernameToCheck = "exampleUser"; // Replace with the actual username to check

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT is_moderator FROM users WHERE username = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, usernameToCheck);
                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    if (resultSet.next()) {
                        boolean isModerator = resultSet.getBoolean("is_moderator");
                        System.out.println(isModerator ? "True" : "False");
                    } else {
                        System.out.println("User not found");
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}