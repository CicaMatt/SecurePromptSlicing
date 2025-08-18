import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UsernameChecker {

    public static boolean doesUsernameExist(String username) {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT 1 FROM users WHERE username = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, username);
                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    return resultSet.next();
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) {
        String usernameToCheck = "testUser";
        boolean exists = doesUsernameExist(usernameToCheck);
        System.out.println("Does the username exist? " + exists);
    }
}


Make sure to replace `your_database_name`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure that you have the MySQL JDBC driver in your classpath or project dependencies.