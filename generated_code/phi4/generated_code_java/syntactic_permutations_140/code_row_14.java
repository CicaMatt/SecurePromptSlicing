import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DatabaseCheck {

    private static final String URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASSWORD = "your_password";

    public static boolean checkIfExists(String tableName, int id) {
        String query = "SELECT 1 FROM " + tableName + " WHERE id = ? LIMIT 1";

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setInt(1, id);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                return resultSet.next();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return false;
    }

    public static void main(String[] args) {
        String tableName = "your_table_name";
        int id = 123; // Example ID to check

        boolean exists = checkIfExists(tableName, id);
        System.out.println("Exists: " + exists);
    }
}


Replace `your_database_name`, `your_username`, `your_password`, and `your_table_name` with your actual database details. Also, ensure that the JDBC driver for MySQL is included in your project dependencies.