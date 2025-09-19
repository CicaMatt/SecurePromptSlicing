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
        String usernameToCheck = "exampleUsername";

        boolean exists = checkIfUsernameExists(url, user, password, usernameToCheck);
        System.out.println("Does the username exist? " + exists);
    }

    public static boolean checkIfUsernameExists(String url, String dbUser, String dbPassword, String username) {
        String query = "SELECT 1 FROM users WHERE username = ? LIMIT 1";
        try (Connection connection = DriverManager.getConnection(url, dbUser, dbPassword);
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


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, user, and password. Also, ensure that the JDBC driver for MySQL is included in your project's classpath.