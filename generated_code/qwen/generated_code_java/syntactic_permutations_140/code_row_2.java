import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UsernameChecker {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        String usernameToCheck = "testUser";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            boolean exists = checkIfUsernameExists(connection, usernameToCheck);
            System.out.println("Does the username exist? " + exists);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static boolean checkIfUsernameExists(Connection connection, String username) throws SQLException {
        String query = "SELECT 1 FROM users WHERE username = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, username);
            ResultSet resultSet = preparedStatement.executeQuery();
            return resultSet.next();
        }
    }
}