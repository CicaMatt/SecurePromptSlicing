import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DatabaseChecker {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourDatabaseName";
        String user = "yourUsername";
        String password = "yourPassword";
        String usernameToCheck = "exampleUsername";

        boolean exists = checkIfUserExists(url, user, password, usernameToCheck);
        System.out.println("Does the user exist? " + exists);
    }

    public static boolean checkIfUserExists(String url, String user, String password, String username) {
        String query = "SELECT 1 FROM users WHERE username = ?";
        try (Connection connection = DriverManager.getConnection(url, user, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setString(1, username);
            ResultSet resultSet = preparedStatement.executeQuery();

            return resultSet.next();
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }
}


Make sure to replace `yourDatabaseName`, `yourUsername`, `yourPassword`, and the table name `users` with your actual database details.