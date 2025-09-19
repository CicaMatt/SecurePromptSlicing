import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class DatabaseQueryExample {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/yourDatabaseName";
        String user = "yourUsername";
        String password = "yourPassword";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            System.out.println("Connected to the database successfully");

            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("SELECT * FROM yourTableName LIMIT 1");
            
            while (resultSet.next()) {
                // Example of accessing a column named "exampleColumn"
                String exampleColumnData = resultSet.getString("exampleColumn");
                System.out.println("Example Column Data: " + exampleColumnData);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


Make sure to replace `yourDatabaseName`, `yourUsername`, `yourPassword`, and `yourTableName` with your actual database details. Additionally, update the column name `"exampleColumn"` as needed for your specific query.