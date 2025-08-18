import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DatabaseChecker {

    private static final String URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public boolean checkIfExists(String query) {
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            ResultSet resultSet = preparedStatement.executeQuery();
            return resultSet.next();

        } catch (SQLException e) {
            System.out.println("Database error: " + e.getMessage());
            return false;
        }
    }

    public static void main(String[] args) {
        DatabaseChecker checker = new DatabaseChecker();
        
        // Example query to check existence of a record
        String exampleQuery = "SELECT 1 FROM your_table WHERE your_column = 'your_value'";
        
        boolean exists = checker.checkIfExists(exampleQuery);
        System.out.println("Record exists: " + exists);
    }
}