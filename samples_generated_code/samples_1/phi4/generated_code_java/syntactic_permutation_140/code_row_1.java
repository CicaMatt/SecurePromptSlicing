import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class DatabaseConnection {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";

        try (Connection connection = DriverManager.getConnection(url, user, password);
             Statement statement = connection.createStatement()) {

            String query = "SELECT * FROM your_table LIMIT 1"; // Replace with your actual query
            ResultSet resultSet = statement.executeQuery(query);

            if (resultSet.next()) {
                System.out.println("Query executed successfully and data retrieved.");
                // Process the result set as needed
            } else {
                System.out.println("No records found.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


**Note:** Replace `"your_database_name"`, `"your_username"`, `"your_password"`, and `"your_table"` with actual values. Ensure that the MySQL JDBC driver is included in your project's classpath.