import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UsernameChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public boolean checkUsernameExists(String username) {
        String query = "SELECT 1 FROM users WHERE username = ?";
        
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            
            preparedStatement.setString(1, username);
            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                return resultSet.next();
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) {
        UsernameChecker checker = new UsernameChecker();
        String testUsername = "testUser";
        boolean exists = checker.checkUsernameExists(testUsername);
        System.out.println("Does the username '" + testUsername + "' exist? " + exists);
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure that you have the MySQL JDBC driver in your classpath or include it as a dependency if using a build tool like Maven or Gradle.