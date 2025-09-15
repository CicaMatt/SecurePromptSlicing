import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class DatabaseConnection {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            if (connection != null) {
                System.out.println("Connected to the database!");

                Statement statement = connection.createStatement();
                String query = "SELECT 1"; // Simple query to check connection
                ResultSet resultSet = statement.executeQuery(query);

                if (resultSet.next()) {
                    int result = resultSet.getInt(1);
                    System.out.println("Query executed successfully, result: " + result);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
