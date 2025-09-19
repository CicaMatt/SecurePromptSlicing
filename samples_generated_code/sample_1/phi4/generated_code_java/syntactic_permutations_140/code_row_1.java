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
            if (connection.isValid(5)) {
                System.out.println("Connected to the database.");

                String query = "SELECT 1"; // Example query to check connection
                try (Statement statement = connection.createStatement();
                     ResultSet resultSet = statement.executeQuery(query)) {

                    while (resultSet.next()) {
                        int value = resultSet.getInt(1);
                        System.out.println("Query executed successfully. Result: " + value);
                    }
                } catch (SQLException e) {
                    System.err.println("Error executing query: " + e.getMessage());
                }

            } else {
                System.err.println("Failed to connect to the database.");
            }
        } catch (SQLException e) {
            System.err.println("Database connection error: " + e.getMessage());
        }
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Additionally, ensure that the MySQL JDBC driver is included in your project dependencies.