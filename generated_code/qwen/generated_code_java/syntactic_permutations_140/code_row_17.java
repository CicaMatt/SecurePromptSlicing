import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UsernameChecker {

    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";

        boolean exists = checkUsernameExists(url, user, password, "testuser");
        System.out.println("Does the username exist? " + exists);
    }

    public static boolean checkUsernameExists(String url, String user, String password, String username) {
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
